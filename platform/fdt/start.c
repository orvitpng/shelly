#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>

#include <cpu.h>
#include <heap.h>

#include <driver/fdt.h>

extern noreturn void _idle();

// remove me!
void printf(const char* fmt, ...);

noreturn void start(uintptr_t cpu, const struct fdt_header* fdt_h)
{
    fdt_t fdt;
    if (!fdt_init(&fdt, fdt_h))
        _idle();

    fdt_node_t node;

    fdt_next(&fdt, &node);
    while (fdt_next(&fdt, &node))
        printf("name: \"%s\"\n", node.name);

    _idle();
}
