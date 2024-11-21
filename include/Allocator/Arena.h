#ifndef ARENA_H
#define AREnA_H

#include <allocator/allocator.h>
#include <common.h>

typedef struct arena_allocator {
	void *base;
	size_t size;
	size_t offset;
	size_t committed;
} Arena;


/*
 * align_forward: 
 * Aligns a memory address forward to the next specified power-of-two boundary
 * @param ptr: Memory address to align (as uintptr_t)
 * @param alignment: Desired alignment value (must be power of 2)
 * @return Aligned address, or 0 if alignment is not a power of 2
 * @example align_forward(74, 8) returns 80 (next 8-byte aligned address)
 */

usize
align_forward(usize ptr, size_t alignment);

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
arena_alloc_aligned(Arena *a, size_t size, size_t alignment);

void *
arena_alloc(size_t size, void *context);

//does nothing for arenas
void *
arena_free(size_t size, void *ptr, void *context);

void 
arena_free_all(void *context);

Arena
arena_init(void *buffer, size_t size);

void
arena_print(const Arena *arena);

#define arena_alloc_init(a) (Allocator) { arena_alloc, arena_free, a }

#endif //ARENA
