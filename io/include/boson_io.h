#pragma once
/*
    boson_io.h: All IO functionality for the Boson engine
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include <errno.h>

#include "../../util/include/boson_string.h"

typedef enum bIOError
{
    B_READALL_OK        =  0,   /* Success */
    B_READALL_INVALID   = -1,   /* Invalid parameters */
    B_READALL_ERROR     = -2,   /* Stream error */
    B_READALL_TOOMUCH   = -3,   /* Too much input */
    B_READALL_NOMEM     = -4    /* Out of memory */
}
bIOError;

bIOError bReadByteStream(FILE *in, uint8_t **dataptr, size_t *sizeptr);
bIOError bReadCharStream(FILE *in, char **dataptr, size_t *sizeptr);
String bLoadCharStream(const char * filepath);
bIOError bWriteByteStream(const char * filepath, uint8_t * byte_stream, size_t size);
bIOError bWriteCharStream(const char * filepath, const char * stream, size_t size);
