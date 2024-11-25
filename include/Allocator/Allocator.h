#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>

#include <common.h>

//! Arena Allocator funcs
typedef struct arena_allocator {
	void *base;
	size_t size;
	size_t offset;
	size_t committed;
} Arena;

/**
 * @brief Aligns a memory address forward to the next specified power-of-two boundary.
 * 
 * @param ptr Memory address to align (as uintptr_t).
 * @param alignment Desired alignment value (must be power of 2).
 * @return Aligned address, or 0 if alignment is not a power of 2.
 * @example align_forward(74, 8) returns 80 (next 8-byte aligned address).
 */
usize
align_forward(usize ptr, size_t alignment);

/**
 * @brief Allocates memory with specified alignment within an arena.
 * 
 * @param arena Pointer to the arena allocator.
 * @param size Desired allocation size in bytes.
 * @param alignment Desired alignment value (must be power of 2).
 * @return Pointer to aligned memory block if successful, NULL if allocation fails or 
 *         if remaining space in the arena is insufficient.
 */
void *
arena_alloc_aligned(Arena *a, size_t size, size_t alignment);

/**
 * @brief Allocates memory within an arena without specific alignment.
 * 
 * @param size Desired allocation size in bytes.
 * @param context Pointer to the arena allocator (cast to void*).
 * @return Pointer to memory block if successful, NULL if allocation fails.
 */
void *
arena_alloc(size_t size, void *context);

/**
 * @brief Frees memory in an arena. This function is a no-op since arenas do not support 
 * freeing individual blocks of memory.
 * 
 * @param size Size of the memory block to free (unused in this implementation).
 * @param ptr Pointer to the memory block to free (unused in this implementation).
 * @param context Pointer to the arena allocator (cast to void*).
 * @return Always returns NULL as this is a no-op.
 */
void *
arena_free(size_t size, void *ptr, void *context);

/**
 * @brief Frees all memory allocated within an arena, effectively resetting the arena.
 * 
 * @param context Pointer to the arena allocator (cast to void*).
 */
void 
arena_free_all(void *context);

/**
 * @brief Initializes an arena allocator with a given buffer and size.
 * 
 * @param buffer Pointer to the memory buffer to manage.
 * @param size Total size of the buffer in bytes.
 * @return An initialized Arena structure.
 */
Arena
arena_init(void *buffer, size_t size);

/**
 * @brief Prints the internal state of an arena allocator for debugging purposes.
 * 
 * @param arena Pointer to the arena allocator to print.
 */
void
arena_print(const Arena *arena);

/**
 * @brief Initializes an arena allocator within an Allocator abstraction.
 * 
 * @param a Pointer to the arena allocator.
 * @return An initialized Allocator structure using the arena allocator.
 */
#define arena_alloc_init(a) (Allocator) { arena_alloc, arena_free, a }

//! GPA Allocator funcs
/**
 * @brief Allocates memory using a general-purpose allocator.
 * 
 * @param size Desired allocation size in bytes.
 * @param context Pointer to the general-purpose allocator context (cast to void*).
 * @return Pointer to memory block if successful, NULL if allocation fails.
 */
void *
gpa_alloc(size_t size, void *context);

/**
 * @brief Frees memory allocated using a general-purpose allocator.
 * 
 * @param size Size of the memory block to free.
 * @param ptr Pointer to the memory block to free.
 * @param context Pointer to the general-purpose allocator context (cast to void*).
 * @return NULL after freeing the memory.
 */
void *
gpa_free(size_t size, void *ptr, void *context);

#endif // ALLOCATOR_H