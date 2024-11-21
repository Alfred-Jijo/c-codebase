#ifndef GPA_H
#define GPA_H

#include <stdlib.h>

void *
gpa_alloc(size_t size, void *context);

void *
arena_free(size_t size, void *ptr, void *context);

#endif //GPA_H