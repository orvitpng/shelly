#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>

#include <cpu.h>
#include <heap.h>

#include "fdt.h"

// remove me!
void printf(const char* fmt, ...);

extern noreturn void _park();

bool init(const struct fdt_header* header)
{
    fdt_t fdt;
    if (!fdt_init(&fdt, header))
        return false;

    fdt_node_t node;

    fdt_next(&fdt, &node);
    while (fdt_next(&fdt, &node))
        printf("name: \"%s\"\n", node.name);
    return true;
}

noreturn void main(uint8_t core, const struct fdt_header* fdt)
{
    if (!init(fdt))
        _park();
    _park();
}
