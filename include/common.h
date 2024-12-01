#ifndef COMMON_H 
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

//! Macros
#define KB (1024ULL)
#define MB (KB * 1024)
#define GB (MB * 1024)
#define DEFAULT_ALIGNMENT (sizeof(void *) * 2)
#define is_power_of_two(x) (x != 0 && (x & (x - 1)) == 0)

#define bool  _Bool
#define false 0
#define true  1

#define local static
#define global static
#define function static

#define private static
#define public extern
#define c_link extern "C"
#define c_link_begin extern "C" {
#define c_link_end }

//! typedefs
typedef intptr_t isize;
typedef uintptr_t usize;

typedef uint8_t byte;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  b8;
typedef int16_t b16;
typedef int32_t b32;
typedef int64_t b64;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef uint8_t uchar;

typedef float f32;
typedef double f64;
typedef long double f128;


// size_t PAGE_SIZE = 0;

global i8  min_i8  = (i8)  0x80;
global i16 min_16  = (i16) 0x8000;
global i32 min_i32 = (i32) 0x80000000;
global i64 min_i64 = (i64) 0x8000000000000000llu;

global i8  max_i8  = (i8)  0x7f;
global i16 max_i16 = (i16) 0x7fff;
global i32 max_i32 = (i32) 0x7fffffff;
global i64 max_i64 = (i64) 0x7fffffffffffffffllu;

#endif // COMMOM_H


