// This file intends to expose functions that are CPU dependent. This isn't
// really important right now as we only target RISC-V, but it might be fun to
// target more platforms in the future, which may be done considerably easier
// with these abstractions implemented early.

#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "builtin.h"

inline uint32_t be32(uint32_t a)
{
    return bswap32(a);
}

#endif
