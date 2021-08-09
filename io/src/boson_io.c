#include "../include/boson_io.h"

/* 
Reads seqential chunks into a stream until it can't anymore,
avoids seeking because pipes and sockets aren't seekable.

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
        return B_READALL_INVALID;

    /* A read error already occurred? */
    if (ferror(in))
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return B_READALL_ERROR;
    }

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
                return B_READALL_TOOMUCH;
            }

            temp = realloc(data, size);
            /* If out of memory */
            if (temp == NULL) 
            {
                free(data);
                return B_READALL_NOMEM;
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
        return B_READALL_ERROR;
    }

    temp = realloc(data, used + 1);
    if (temp == NULL) 
    {
        free(data);
        return B_READALL_NOMEM;
    }
    data = temp;
    //data[used] = '\0';

    *dataptr = data;
    *sizeptr = used;

    return B_READALL_OK;
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
        return B_READALL_INVALID;

    /* A read error already occurred? */
    if (ferror(in))
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return B_READALL_ERROR;
    }

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
                return B_READALL_TOOMUCH;
            }

            temp = realloc(data, size);
            /* If out of memory */
            if (temp == NULL) 
            {
                free(data);
                return B_READALL_NOMEM;
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
        return B_READALL_ERROR;
    }

    temp = realloc(data, used + 1);
    if (temp == NULL) 
    {
        free(data);
        return B_READALL_NOMEM;
    }
    data = temp;
    data[used] = '\0';

    *dataptr = data;
    *sizeptr = used;

    return B_READALL_OK;
}

String bLoadCharStream(const char * filepath)
{
    FILE * fp = fopen(filepath, "r");
    if (ferror(fp))
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
    FILE * fp = fopen(filepath, "rb");
    if (ferror(fp))
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }
    uint8_t * data;
    if (bReadByteStream(fp, &data, sizeptr) != B_READALL_OK)
        return NULL;

    return data;
}

bIOError bWriteByteStream(const char * filepath, uint8_t * byte_stream, size_t size)
{
    FILE * fp = fopen(filepath, "wb");
    if (ferror(fp))
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return B_READALL_ERROR;
    }
    fwrite((void*)byte_stream, 1, size, fp);
    fclose(fp);
    return B_READALL_OK;
}

bIOError bWriteCharStream(const char * filepath, const char * stream, size_t size)
{
    FILE * fp = fopen(filepath, "w");
    if (ferror(fp))
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return B_READALL_ERROR;
    }
    fwrite((void*)stream, sizeof(char), size, fp);
    fclose(fp);
    return B_READALL_OK;
}
