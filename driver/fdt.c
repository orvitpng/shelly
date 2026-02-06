#include <cpu.h>
#include <stdint.h>

#include <def.h>
#include <driver/fdt.h>

#define FDT_VERSION 17
#define FDT_MAGIC 0xd00dfeed

#define FDT_BEGIN_NODE 1
#define FDT_END_NODE 2
#define FDT_PROP 3
#define FDT_NOP 4
#define FDT_END 9

bool fdt_init(fdt_t* fdt, const struct fdt_header* header)
{
    if (be32(header->last_comp_version) > FDT_VERSION)
        return false;

    fdt->header = header;
    fdt->ptr = (const uint32_t*)((const uint8_t*)header
        + be32(header->off_dt_struct));

    return true;
}

bool fdt_next(fdt_t* fdt, fdt_node_t* node)
{
    const uint32_t* cur = fdt->ptr;
    uint32_t tag;

    while ((tag = be32(*cur++)) != FDT_END) {
        switch (tag) {
        case FDT_END_NODE:
        case FDT_NOP:
            continue;

        case FDT_PROP: {
            uint32_t len = be32(*cur++);
            cur = ALIGN_PTR(const uint32_t, (uintptr_t)(cur + 1) + len);
            continue;
        }

        case FDT_BEGIN_NODE:
            break;

        default:
            return false;
        }

        const uint8_t* ptr = (const uint8_t*)cur;
        node->name = ptr;

        while (*ptr++)
            ;

        node->ptr = ALIGN_PTR(const uint32_t, ptr);
        fdt->ptr = node->ptr;

        return true;
    }

    return false;
}
