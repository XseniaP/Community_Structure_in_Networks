/** safe_memory module summary:
 *
 * this module implements safe dynamic memory allocation, checks for errors
 *
 * The module implements the following Functions:
 * safe_malloc - dynamically allocates memory space of specified size and returns the pointer
 *               to the first byte of allocation; performs error checks, in case of NULL pointer program is interrupted
 *               and error code returned;
 * safe_calloc - allocates the space for elements of an array; initializes the elements to zero and returns a pointer to
 *               the memory; performs error checks, in case of NULL pointer program is interrupted and error code returned;
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROJECT_TOHNA_SAFE_MEMORY_H
#define PROJECT_TOHNA_SAFE_MEMORY_H

void* safe_malloc(size_t size);
void* safe_calloc(int number, size_t size);

#endif
