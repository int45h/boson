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
    READALL_OK          =  0,   /* Success */
    READALL_INVALID     = -1,   /* Invalid parameters */
    READALL_ERROR       = -2,   /* Stream error */
    READALL_TOOMUCH     = -3,   /* Too much input */
    READALL_NOMEM       = -4    /* Out of memory */
}
bIOError;

bIOError bReadByteStream(FILE *in, uint8_t **dataptr, size_t *sizeptr);
bIOError bReadCharStream(FILE *in, char **dataptr, size_t *sizeptr);
String bLoadCharStream(const char * filepath);