#include "../include/boson_io.h"

/* 
Reads in a file stream without seeking to the end of the file.

Reads seqential chunks into a stream until it can't anymore.

From https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer 
*/
bIOError bReadByteStream(FILE *in, uint8_t **dataptr, size_t *sizeptr)
{
    const size_t READALL_CHUNK = 256 * 1024; // 256 KiB
    
    uint8_t *data   = NULL, 
            *temp;
    size_t  size    = 0,
            used    = 0,
            n;

    /* None of the parameters can be NULL. */
    if (in == NULL || dataptr == NULL || sizeptr == NULL)
        return READALL_INVALID;

    /* A read error already occurred? */
    if (ferror(in))
        return READALL_ERROR;

    /* Read until no longer possible */
    do
    {
        if (used + READALL_CHUNK + 1 > size) 
        {
            size = used + READALL_CHUNK + 1;

            /* Overflow check. Some ANSI C compilers
               may optimize this away, though. */
            if (size <= used) 
            {
                free(data);
                return READALL_TOOMUCH;
            }

            temp = realloc(data, size);
            /* If out of memory */
            if (temp == NULL) 
            {
                free(data);
                return READALL_NOMEM;
            }
            data = temp;
        }

        n = fread(data + used, 1, READALL_CHUNK, in);
        if (n == 0)
            break;

        used += n;
    }
    while (true);

    if (ferror(in)) 
    {
        free(data);
        return READALL_ERROR;
    }

    temp = realloc(data, used + 1);
    if (temp == NULL) 
    {
        free(data);
        return READALL_NOMEM;
    }
    data = temp;
    //data[used] = '\0';

    *dataptr = data;
    *sizeptr = used;

    return READALL_OK;
}

bIOError bReadCharStream(FILE *in, char **dataptr, size_t *sizeptr)
{
    const size_t READALL_CHUNK = 256 * 1024; // 256 KiB
    
    char    *data   = NULL, 
            *temp;
    size_t  size    = 0,
            used    = 0,
            n;

    /* None of the parameters can be NULL. */
    if (in == NULL || dataptr == NULL || sizeptr == NULL)
        return READALL_INVALID;

    /* A read error already occurred? */
    if (ferror(in))
        return READALL_ERROR;

    /* Read until no longer possible */
    do
    {
        if (used + READALL_CHUNK + 1 > size) 
        {
            size = used + READALL_CHUNK + 1;

            /* Overflow check. Some ANSI C compilers
               may optimize this away, though. */
            if (size <= used) 
            {
                free(data);
                return READALL_TOOMUCH;
            }

            temp = realloc(data, size);
            /* If out of memory */
            if (temp == NULL) 
            {
                free(data);
                return READALL_NOMEM;
            }
            data = temp;
        }

        n = fread(data + used, 1, READALL_CHUNK, in);
        if (n == 0)
            break;

        used += n;
    }
    while (true);

    if (ferror(in)) 
    {
        free(data);
        return READALL_ERROR;
    }

    temp = realloc(data, used + 1);
    if (temp == NULL) 
    {
        free(data);
        return READALL_NOMEM;
    }
    data = temp;
    data[used] = '\0';

    *dataptr = data;
    *sizeptr = used;

    return READALL_OK;
}

String bLoadCharStream(const char * filepath)
{
    FILE * fp;
    if ((fp = fopen(filepath, "r")) == NULL)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return (String){NULL, 0};
    }

    String str;

    bReadCharStream(fp, &str.c_str, &str.size);
    fclose(fp);
    
    return str;
}

uint8_t* bLoadByteStream(const char * filepath, size_t *sizeptr)
{
    FILE * fp;
    if ((fp = fopen(filepath, "rb")) == NULL)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }
    uint8_t * data;
    if (bReadByteStream(fp, &data, sizeptr) != READALL_OK)
        return NULL;

    return data;
}