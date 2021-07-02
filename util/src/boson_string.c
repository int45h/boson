#include "../include/boson_string.h"

String bNewString(const char * in_str)
{
    size_t size = strlen(in_str);
    String str = (String){
        (char*) malloc(size * sizeof(char)),
        size
    };
    //memcpy((void*)str.c_str, (void*)in_str, size*sizeof(char));
    strncpy(str.c_str, in_str, size);
}

void bDestroyString(String * str)
{
    if (str->c_str != NULL)
        free(str->c_str);
    str->size = 0;
}

void bStrResize(String * str, const size_t size)
{
    str->size += size;
    str->c_str = (char*) realloc((void*)str->c_str, str->size * sizeof(char*));
}

void bStrAppend(String * str, const char * append)
{
    //size_t  size    = strlen(append),
    //        end     = str->size;
    //bStrResize(str, size);
    //memcpy((void*)&str->c_str[end], (void*)append, size*sizeof(char));
    strncat(str->c_str, append, strlen(append));
}

void bStrAppendTo(String * str, const char * append, const size_t size)
{
    size_t end = str->size;
    bStrResize(str, size);
    memcpy((void*)&str->c_str[end], (void*)append, size*sizeof(char));
}
