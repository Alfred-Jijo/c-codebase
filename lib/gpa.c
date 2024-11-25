#include <allocator/allocator.h>

void *
gpa_alloc(size_t size, void *context) {
    (void) context;
    return malloc(size);
}

void *
gpa_free(size_t size, void *ptr, void *context) {
    (void)size;
    (void)context;
    free(ptr);
    return (ptr = NULL);
}