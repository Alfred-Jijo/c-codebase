#define ARENA_IMPLEMENTATION  
#include "Allocator.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1 * KB;
    void *buffer = malloc(size);

    Arena arena = arena_init(buffer, size);
    Allocator all = arena_alloc_init(&arena);

    u8 *x = make(u8, 420, all);
    size_t *y = make(size_t, 23, all);
    char *z = make(char, 69, all);

    for (int i = 0; i < 420; i += 1) {
        x[i] = i;
    } 

    for (int i = 0; i < 23; i += 1) {
        y[i] = (size_t)i;
    }

    for (int i = 0; i < 69; i += 1)  {
        z[i] = (char)i + '!';
    }

    release(size, arena.base, all);
    return 0;
}
