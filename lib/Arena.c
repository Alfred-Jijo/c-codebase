#include <Allocator/Allocator.h>
#include <Allocator/Arena.h>

/*
 * align_forward: 
 * Aligns a memory address forward to the next specified power-of-two boundary
 * @param ptr: Memory address to align (as uintptr_t)
 * @param alignment: Desired alignment value (must be power of 2)
 * @return Aligned address, or 0 if alignment is not a power of 2
 * @example align_forward(74, 8) returns 80 (next 8-byte aligned address)
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


/*
 * arena_alloc_aligned: 
 * Aligns a memory address forward to the next specified power-of-two boundary in the arena buffer
 * @param arena: Memory address to align (as uintptr_t)
 * @param size: Desired allocation size in bytes
 * @param alignment: Desired alignment value (must be power of 2)
 * @return Pointer to aligned memory block if successful, NULL if allocation fails or 
 *         if remaining space in arena is insufficient
 * @note Example: align_forward(74, 8) returns 80 (next 8-byte aligned address)
*/
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

//does nothing for arenas
void *
arena_free(size_t size, void *ptr, void *context) {
    (void)size;
    (void)ptr;
    (void)context;
    return 0;
}

void 
arena_free_all(void *context) {
    Arena *a = (Arena *)context;
    a->offset = 0;
    a->committed = 0;
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
    printf("base: %p, commited: %zu, size: %zu\n", arena->base, arena->committed, arena->size);
}