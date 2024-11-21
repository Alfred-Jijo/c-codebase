#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>

#include <common.h>

typedef struct common_allocator {
    void *(*alloc) (size_t size, void *context);
    void *(*free) (size_t size, void *ptr, void *context);
    void *context;
} Allocator;


//! MACROS
/*
 * make:
 * Allocates memory for an array of elements of type T
 * @param T: The type of elements to allocate
 * @param n: Number of elements to allocate
 * @param a: Allocator structure containing allocation functions and context
 * @return Pointer to the allocated memory, cast to type T*
 * @note Returns NULL if allocation fails
 */
#define make(T, n, a) ((T *)((a).alloc(sizeof(T) * (n), (a).context)))

/*
 * release:
 * Releases previously allocated memory using the provided allocator
 * @param s: Size of the memory block to free in bytes
 * @param p: Pointer to the memory block to free
 * @param a: Allocator structure containing free functions and context
 */
#define release(s, p, a) ((a).free((s), (p), (a).context))


#endif //ALLOCATOR_H
