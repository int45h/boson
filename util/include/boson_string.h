#pragma once
/*
    boson_string.h: Optional string functions for the Boson engine
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include <errno.h>

typedef struct String
{
    char*   c_str;
    size_t  size;
}
String;

String bNewString(const char * in_str);

void bDestroyString(String * str);
void bStrResize(String * str, const size_t size);
void bStrAppend(String * str, const char * append);
void bStrAppendTo(String * str, const char * append, const size_t size);