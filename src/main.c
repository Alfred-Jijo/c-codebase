#include <stdio.h>
#include <stdlib.h>

#include <allocator/allocator.h>
#include <dsa.h>
#include <common.h>


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
    
    u8 *my_array = array(u8, &allocator);

    printf("Adding elements to the array:\n");
    for (size_t i = 0; i <= 5; ++i) {
        array_append(my_array, i);
    }

    printf("Array contents after appending:\n");
    for (size_t i = 0; i < array_length(my_array); i++) {
        printf("my_array[%zu] = %d\n", i, my_array[i]);
    }

    printf("\nRemoving element at index 2:\n");
    array_remove(my_array, 2);

    printf("Array contents after removal:\n");
    for (size_t i = 0; i < array_length(my_array); i++) {
        printf("my_array[%zu] = %d\n", i, my_array[i]);
    }

    printf("\nPopping the last element:\n");
    array_pop_back(my_array);

    printf("Array contents after popping:\n");
    for (size_t i = 0; i < array_length(my_array); i++) {
        printf("my_array[%zu] = %d\n", i, my_array[i]);
    }

    goto cleanup;

cleanup:
    printf("\n");
    arena_print(&arena);
    arena_free_all(&arena);
    free(buffer);
    buffer = NULL;
    arena.base = buffer;
    arena_print(&arena);
    
    free(array_header(my_array));

    return EXIT_SUCCESS;
}
