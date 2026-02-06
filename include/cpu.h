#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include <builtin.h>

static inline uint32_t be32(uint32_t a)
{
    return bswap32(a);
}

#endif
