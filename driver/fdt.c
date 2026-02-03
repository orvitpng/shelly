#include <cpu.h>

#include "fdt.h"

#define FDT_VERSION 17
#define FDT_MAGIC 0xd00dfeed

#define FDT_BEGIN_NODE 1
#define FDT_END_NODE 2
#define FDT_PROP 3
#define FDT_NOP 4
#define FDT_END 9

bool fdt_init(fdt* fdt, const struct fdt_header* header)
{
    if (be32(header->magic) != FDT_MAGIC
        || be32(header->last_comp_version) > FDT_VERSION)
        return false;

    return true;
}
