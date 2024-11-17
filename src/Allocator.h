#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "common.h"

typedef struct common_allocator {
    void *(*alloc_func) (size_t size, void *context);
    void *(*free_func) (size_t size, void *ptr, void *context);
    void *context;
} Allocator;

typedef struct arena_allocator {
    void *base;
    size_t size;
    size_t offset;
    size_t committed;
} Arena;

/*
 * @Function: make
 * @Description: Allocates memory for an array of elements of type T
 * @param T: The type of elements to allocate
 * @param n: Number of elements to allocate
 * @param a: Allocator structure containing allocation functions and context
 * @return: Pointer to the allocated memory, cast to type T*
 * @note: Returns NULL if allocation fails
 */
#define make(T, n, a) ((T *)((a).alloc_func(sizeof(T) * (n), (a).context)))

/*
 * @Function: release
 * @Description: Releases previously allocated memory using the provided allocator
 * @param s: Size of the memory block to free in bytes
 * @param p: Pointer to the memory block to free
 * @param a: Allocator structure containing free functions and context
 */
#define release(s, p, a) ((a).free_func((s), (p), (a).context))

// #ifndef ARENA_IMPLEMENTATION

usize align_forward(usize ptr, size_t alignment);
void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);
void *arena_alloc(size_t size, void *context);
void *arena_free(size_t size, void *ptr, void *context);
void arena_free_all(void *context);
Arena arena_init(void *buffer, size_t size);

#define arena_alloc_init(a) (Allocator){arena_alloc, arena_free, a}
//#endif //ARENA_IMPLEMENTATION
#endif //ALLOCATOR_H
