//
//  jsonFormatter.c
//  Json Formatter
//
//  Created by Gonzo Fialho on 4/29/14.
//  Copyright (c) 2014 CEAFDC. All rights reserved.
//

#include "jsonFormatter.h"

#define YES 1
#define NO 0

typedef char bool;

#define MAXBUFLEN 65535

bool charIsNumber(char c)
{
    static const char * string = "0123456789-.Ee+falsetruenull";
    int i;
    for (i =0; string[i]; i++)
        if (c==string[i])
            return YES;
    return NO;
}

int formatJson(FILE * inFile, FILE * outFile, const char * tab, bool useColors)
{
    bool isInString = NO;
    bool isInNumber = NO;
    bool charIsEscaped = NO;
    int identationLevel = 0;
    char c;
    char source[MAXBUFLEN];

    while (YES)
    {
        size_t newLen = fread(source, sizeof(char), MAXBUFLEN, inFile);
        if (newLen == 0)
            break;
        else
        {
            int i;
            for (i = 0; i < newLen; i++)
            {
                c = source[i];
                if (c == '\"' && !charIsEscaped)
                {
                    isInString = !isInString;
                    if (isInString)
                    {
                        if (useColors)
                            fprintf(outFile, "\033[0;31m%c", c);
                        else
                            fwrite(&c, sizeof(char), 1, outFile);
                        continue;
                    }
                    else
                    {
                        if (useColors)
                            fprintf(outFile, "%c\033[0m", c);
                        else
                            fwrite(&c, sizeof(char), 1, outFile);
                        continue;
                    }
                }
                if (!charIsEscaped && c == '\\')
                    charIsEscaped = YES;
                else
                    charIsEscaped = NO;

                if (isInString)
                {
                    fwrite(&c, sizeof(char), 1, outFile);
                    continue;
                }

                if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
                    continue;

                if (charIsNumber(c))
                {
                    if (!isInNumber)
                    {
                        if (useColors)
                            fprintf(outFile, "\033[0;35m%c", c);
                        else
                            fwrite(&c, sizeof(char), 1, outFile);
                        isInNumber = YES;
                    }
                    else
                        fwrite(&c, sizeof(char), 1, outFile);
                    continue;
                }
                else if (isInNumber)
                {
                    if (useColors)
                        fprintf(outFile, "\033[0m");
                    isInNumber = NO;
                }

                if (c == ':')
                {
                    fprintf(outFile, ": ");
                    continue;
                }

                if (c == '{' || c == '[')
                {
                    identationLevel++;
                    fprintf(outFile, "%c\n", c);
                    int j;
                    for (j = 0; j < identationLevel; j++)
                        fputs(tab, outFile);
                    continue;
                }

                if (c == '}' || c == ']')
                {
                    identationLevel--;
                    fputs("\n", outFile);
                    int j;
                    for (j = 0; j < identationLevel; j++)
                        fputs(tab, outFile);
                    fwrite(&c, sizeof(char), 1, outFile);
                    continue;
                }

                if (c == ',')
                {
                    fputs(",\n", outFile);
                    int j;
                    for (j = 0; j < identationLevel; j++)
                        fputs(tab, outFile);
                    continue;
                }

                if (useColors && (isInNumber || isInNumber))
                    fputs("\033[0m", outFile);

                return -1;

            }
        }
        if (newLen < MAXBUFLEN)
            break;
    }

    fputs("\n", outFile);

    return 0;
}
