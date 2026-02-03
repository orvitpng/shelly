#ifndef DEF_H
#define DEF_H

#include <stddef.h>

#include "def.S"

#define ALIGN(a, b) ((a) & ~((b) - 1))

#define HEAP_ALIGN _Alignof(max_align_t)

#endif
