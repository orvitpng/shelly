extern char __heap[];
extern char __heap_end[];

static char* heap = __heap;

struct alloc_header {
    unsigned int size;
    /* pad to 16 bytes */
    unsigned int pad[3];
};

static struct alloc_header* alloc_header(void* ptr)
{
    return (struct alloc_header*)ptr - 1;
}

static unsigned int align8(unsigned int val)
{
    return (val + 7) & ~7;
}

void memcpy(void* dst, const void* src, unsigned int n)
{
    char* d = dst;
    const char* s = src;

    while (n--)
        *d++ = *s++;
}

/* TODO: add freeing, not just bumps */
void* alloc(unsigned int size)
{
    size = align8(size);
    unsigned int total = sizeof(struct alloc_header) + size;

    if (heap + total > __heap_end)
        return 0;

    struct alloc_header* header = (struct alloc_header*)heap;
    heap += total;

    header->size = size;
    return header + 1;
}

void free(void* ptr)
{
}

void* realloc(void* ptr, unsigned int size)
{
    if (!ptr)
        return alloc(size);
    if (size == 0)
        return 0;

    struct alloc_header* header = alloc_header(ptr);
    unsigned int old_size = header->size;
    unsigned int new_size = align8(size);

    if (new_size == old_size || new_size < old_size)
        return ptr;

    if ((char*)ptr + old_size == heap) {
        unsigned int diff = new_size - old_size;
        if (heap + diff > __heap_end)
            return 0;

        heap += diff;
        header->size = new_size;

        return ptr;
    }

    void* new = alloc(new_size);
    if (!new)
        return 0;

    memcpy(new, ptr, old_size);
    free(ptr);

    return new;
}
