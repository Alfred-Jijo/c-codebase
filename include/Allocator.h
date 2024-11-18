#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <common.h>
#include <stdio.h>
#include <stdlib.h>

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

#ifndef ARENA_IMPLEMENTATION

usize align_forward(usize ptr, size_t alignment);
void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);
void *arena_alloc(size_t size, void *context);
void *arena_free(size_t size, void *ptr, void *context);
void arena_free_all(void *context, void *buffer);
Arena arena_init(void *buffer, size_t size);

/*
 * @Function: align_forward
 * @Description: Aligns a memory address forward to the next specified power-of-two boundary
 * @param ptr: Memory address to align (as uintptr_t)
 * @param alignment: Desired alignment value (must be power of 2)
 * @return: Aligned address, or 0 if alignment is not a power of 2
 * @example: align_forward(74, 8) returns 80 (next 8-byte aligned address)
 */

usize
align_forward(usize ptr, size_t alignment) {
    usize p, a, modulo;
    if (!is_power_of_two(alignment)) {
        return 0;
    }
    p = ptr;
    a = (usize)alignment;
    modulo = p & (a - 1);

    if (modulo) {
        p += a - modulo;
    }

    return p;
}

void *
arena_alloc_aligned(Arena *a, size_t size, size_t alignment) {
    usize curr_ptr = (usize)a->base + (usize)a->offset;
    usize offset = align_forward(curr_ptr, alignment);
    offset -= (usize)a->base;

    if (offset + size > a->size) {
        return 0;
    }

    a->committed += size;
    void *ptr = (u8 *)a->base + offset;
    a->offset = offset + size;

    return ptr;
}

void *
arena_alloc(size_t size, void *context) {
    if (!size) {
        return 0;
    }
    return arena_alloc_aligned((Arena *)context, size, DEFAULT_ALIGNMENT);
}

//does nothing
void *
arena_free(size_t size, void *ptr, void *context) {
    (void)size;
    (void)ptr;
    (void)context;
    return 0;
}


void 
arena_free_all(void *context, void *buffer) {
    Arena *a = (Arena *)context;
    a->offset = 0;
    a->committed = 0;
    free(buffer);
    buffer = NULL;
    a->size = 0;
}

Arena
arena_init(void *buffer, size_t size) {
    return (Arena) {
        .base = buffer,
        .size = size
    };
}

void
arena_print(const Arena *arena) {
    printf("commited: %zu, size: %zu\n", arena->committed, arena->size);
}

#define arena_alloc_init(a) (Allocator) { arena_alloc, arena_free, a }

#endif //ARENA_IMPLEMENTATION
#endif //ALLOCATOR_H
