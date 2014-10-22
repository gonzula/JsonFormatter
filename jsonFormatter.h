//
//  jsonFormatter.h
//  Json Formatter
//
//  Created by Gonzo Fialho on 4/29/14.
//  Copyright (c) 2014 CEAFDC. All rights reserved.
//

#ifndef Json_Formatter_jsonFormatter_h
#define Json_Formatter_jsonFormatter_h

#include <stdio.h>

int formatJson(FILE * inFile, FILE * outFile, const char * tab, char useColors);

#endif
