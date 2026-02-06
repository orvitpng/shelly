#include <stddef.h>
#include <stdint.h>

#include <def.h>

extern uint8_t __heap_start[];
extern uint8_t __heap_end[];

struct alloc_header {
    size_t size;
};

// TODO: this really should be more complicated/not a bumb allocator lol
static void* bump(size_t size)
{
    static uint8_t* heap = __heap_start;

    size = ALIGN(HEAP_ALIGN, size);
    if (size > (size_t)(__heap_end - heap))
        return 0;

    uint8_t* ptr = heap;
    heap += size;
    return ptr;
}

void* alloc(size_t size)
{
    struct alloc_header* header = bump(sizeof(struct alloc_header));
    if (!header)
        return 0;

    header->size = size;
    return bump(size);
}

void* realloc(void* ptr, size_t size)
{
    return 0;
}

void free(void* ptr)
{
}
