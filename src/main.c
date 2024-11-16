#define ARENA_IMPLEMENTATION  // This must come before including the header
#include "Allocator.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    float value;
} Point;

int main() {
    // Create a 64MB buffer for our arena
    size_t arena_size = 64 * MB;
    void *buffer = malloc(arena_size);
    if (!buffer) {
        printf("Failed to allocate buffer for arena\n");
        return 1;
    }

    // Initialize arena and create allocator
    Arena arena = arena_init(buffer, arena_size);
    Allocator allocator = {arena_alloc, arena_free, &arena};  // Direct initialization

    // Allocate some different types of data
    int *numbers = (int *)allocator.alloc_func(sizeof(int) * 10, allocator.context);
    Point *points = (Point *)allocator.alloc_func(sizeof(Point) * 5, allocator.context);
    char *message = (char *)allocator.alloc_func(sizeof(char) * 100, allocator.context);

    if (!numbers || !points || !message) {
        printf("Failed to allocate memory from arena\n");
        free(buffer);
        return 1;
    }

    // Use the allocated memory
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * 2;
    }

    for (int i = 0; i < 5; i++) {
        points[i].x = i;
        points[i].y = i * 2;
        points[i].value = i * 3.14f;
    }

    // Print some values to demonstrate the allocations worked
    printf("Numbers: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");

    printf("Points:\n");
    for (int i = 0; i < 5; i++) {
        printf("Point %d: (%d, %d) value: %f\n", 
               i, points[i].x, points[i].y, points[i].value);
    }

    // Demonstrate allocating more memory
    float *new_data = (float *)allocator.alloc_func(sizeof(float) * 5, allocator.context);
    if (new_data) {
        for (int i = 0; i < 5; i++) {
            new_data[i] = i * 1.5f;
        }
        printf("\nNew float data: ");
        for (int i = 0; i < 5; i++) {
            printf("%f ", new_data[i]);
        }
        printf("\n");
    }

    // Print arena statistics
    printf("\nArena Statistics:\n");
    printf("Total Size: %zu bytes\n", arena.size);
    printf("Committed: %zu bytes\n", arena.committed);
    printf("Current Offset: %zu bytes\n", arena.offset);

    // Free all arena memory at once
    arena_free_all(&arena);
    
    // Free the underlying buffer
    free(buffer);

    return 0;
}
