#include "safe_memory.h"

void* safe_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr && (size > 0)) {
        perror("malloc failed!");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void* safe_calloc(int number, size_t size)
{
    void *ptr = calloc(number,size);

    if (!ptr && (size > 0)) {
        perror("calloc failed!");
        exit(EXIT_FAILURE);
    }

    return ptr;
}
