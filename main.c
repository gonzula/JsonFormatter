//
//  main.c
//  Json Formatter
//
//  Created by Gonzo Fialho on 4/29/14.
//  Copyright (c) 2014 CEAFDC. All rights reserved.
//

#include <unistd.h>
#include "jsonFormatter.h"



int main(int argc, const char * argv[])
{
    int retVal = formatJson(stdin, stdout, "    ", isatty(1));
    if (retVal)
        fprintf(stderr, "InvalidJson\n");
    return retVal;
}

