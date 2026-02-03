#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void* alloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#endif
