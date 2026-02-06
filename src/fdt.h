#ifndef FDT_H
#define FDT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const uint8_t* name;
    const void* ptr;
} fdt_node_t;

struct fdt_header {
    uint32_t magic;
    uint32_t size;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;

    // version 2
    uint32_t boot_cpuid_phys;

    // version 3
    uint32_t size_dt_strings;

    // version 17
    uint32_t size_dt_struct;
};

typedef struct {
    const struct fdt_header* header;
    const void* ptr;
} fdt_t;

bool fdt_init(fdt_t* fdt, const struct fdt_header* header);
bool fdt_next(fdt_t* fdt, fdt_node_t* node);

#endif
