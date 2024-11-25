#ifndef COMMON_H 
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

//! typedefs
typedef intptr_t isize;
typedef uintptr_t usize;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;
typedef long double f128;

typedef uint8_t byte;

// size_t PAGE_SIZE = 0;

typedef struct common_allocator {
    void *(*alloc) (size_t size, void *context);
    void *(*free) (size_t size, void *ptr, void *context);
    void *context;
} Allocator;


//! MACROS
/**
 * make:
 * Allocates memory for an array of elements of type T
 * @param T: The type of elements to allocate
 * @param n: Number of elements to allocate
 * @param a: Allocator structure containing allocation functions and context
 * @return Pointer to the allocated memory, cast to type T*
 * @note Returns NULL if allocation fails
 */
#define make(T, n, a) ((T *)((a).alloc(sizeof(T) * (n), (a).context)))

/**
 * release:
 * Releases previously allocated memory using the provided allocator
 * @param s: Size of the memory block to free in bytes
 * @param p: Pointer to the memory block to free
 * @param a: Allocator structure containing free functions and context
 */
#define release(s, p, a) ((a).free((s), (p), (a).context))


#define bool _Bool
#define false 1
#define true 0

#define KB (1024ULL)
#define MB (KB * 1024)
#define GB (MB * 1024)
#define DEFAULT_ALIGNMENT (sizeof(void *) * 2)
#define is_power_of_two(x) (x != 0 && (x & (x - 1)) == 0)

#define bool  _Bool
#define false 0
#define true  1

#endif // COMMOM_H


