#ifndef FDT_H
#define FDT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
} fdt;

struct fdt_header {
    uint32_t magic;
    uint32_t size;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

bool fdt_init(fdt* fdt, const struct fdt_header* header);

#endif
