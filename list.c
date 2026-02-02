#include "list.h"
#include "mem.h"

#define LIST_DEFINE(name, type)                                           \
    const name name##_empty = { 0 };                                      \
                                                                          \
    int name##_init(name* self, unsigned int cap)                         \
    {                                                                     \
        if (!cap) {                                                       \
            *self = name##_empty;                                         \
            return 1;                                                     \
        }                                                                 \
                                                                          \
        self->len = 0;                                                    \
        self->cap = cap;                                                  \
                                                                          \
        self->data = alloc(cap * sizeof(type));                           \
        if (!self->data)                                                  \
            return 0;                                                     \
                                                                          \
        return 1;                                                         \
    }                                                                     \
                                                                          \
    void name##_deinit(name* self)                                        \
    {                                                                     \
        if (self->data)                                                   \
            free(self->data);                                             \
    }                                                                     \
                                                                          \
    int name##_push(name* self, type val)                                 \
    {                                                                     \
        if (self->len == self->cap) {                                     \
            unsigned int cap = self->cap ? self->cap * 2 : 1;             \
            type* data = realloc(self->data, cap * sizeof(type));         \
            if (!data)                                                    \
                return 0;                                                 \
                                                                          \
            self->cap = cap;                                              \
            self->data = data;                                            \
        }                                                                 \
                                                                          \
        self->data[self->len++] = val;                                    \
        return 1;                                                         \
    }                                                                     \
                                                                          \
    type name##_pop(name* self)                                           \
    {                                                                     \
        return self->data[--self->len];                                   \
    }                                                                     \
                                                                          \
    type* name##_take(name* self)                                         \
    {                                                                     \
        if (!self->data) {                                                \
            type* data = alloc(sizeof(type));                             \
            if (data)                                                     \
                data[0] = 0;                                              \
            return data;                                                  \
        }                                                                 \
                                                                          \
        type* data = realloc(self->data, (self->len + 1) * sizeof(type)); \
        if (!data) {                                                      \
            name##_deinit(self);                                          \
            return 0;                                                     \
        }                                                                 \
                                                                          \
        data[self->len] = 0;                                              \
        return data;                                                      \
    }

LIST_DEFINE(list_char, char)
