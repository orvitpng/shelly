#ifndef MEM_H
#define MEM_H

void memcpy(void* dst, const void* src, unsigned int n);

void* alloc(unsigned int size);
void* realloc(void* ptr, unsigned int size);
void free(void* ptr);

#endif
