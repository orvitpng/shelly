#ifndef DEF_H
#define DEF_H

#define PAGE_SIZE 0x1000

#define STACK_SIZE PAGE_SIZE
#define HEAP_SIZE PAGE_SIZE * 16

#ifndef __ASSEMBLER__

#include <stdalign.h>
#include <stddef.h>

#define ALIGN(align, size) \
    (((size) + (align) - 1) & ~((align) - 1))

#define ALIGN_PTR(type, ptr) \
    ((type*)ALIGN(sizeof(type), (uintptr_t)(ptr)))

#define HEAP_ALIGN alignof(max_align_t)

#endif // !__ASSEMBLER__
#endif // !DEF_H
