#ifndef DEF_H
#define DEF_H

#include <stdalign.h>
#include <stddef.h>

#include "def.inc" // IWYU pragma: export

#define ALIGN(align, size) (((size) + (align) - 1) & ~((align) - 1))

#define HEAP_ALIGN alignof(max_align_t)

#endif
