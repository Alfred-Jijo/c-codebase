#include <Allocator.h>
#include <common.h>

#include <stdio.h>
#include <stdlib.h>


int
main() {
    size_t size = 1 * KB;
    void *buffer = malloc(size);

    Arena arena = arena_init(buffer, size);
    Allocator all = arena_alloc_init(&arena);

    u8 *x = make(u8, 1, all);
    size_t *y = make(size_t, 2, all);
    char *z = make(char, 3, all);

    for (u8 i = 0; i < 1; i += 1) {
        x[i] = i;
    } 

    for (u8 i = 0; i < 2; i += 1) {
        y[i] = (size_t)i;
    }

    for (u8 i = 0; i < 3; i += 1)  {
        z[i] = (char)i + '!';
    }


    arena_print(&arena);
    release(sizeof(u8), x, all);
    arena_print(&arena);
    arena_free_all(&arena, buffer);
    arena_print(&arena);
    return 0;
}
