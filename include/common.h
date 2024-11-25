#ifndef COMMON_H 
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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

#define bool _Bool
#define false 1
#define true 0

#define KB (1024ULL)
#define MB (KB * 1024)
#define GB (MB * 1024)
#define DEFAULT_ALIGNMENT (sizeof(void *) * 2)
#define is_power_of_two(x) (x != 0 && (x & (x - 1)) == 0)

#endif // COMMOM_H
