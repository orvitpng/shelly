#ifndef LIST_H
#define LIST_H

#define LIST_DECLARE(name, type)                   \
    typedef struct name {                          \
        type* data;                                \
        unsigned int len;                          \
        unsigned int cap;                          \
    } name;                                        \
                                                   \
    extern const name name##_empty;                \
                                                   \
    int name##_init(name* self, unsigned int cap); \
    void name##_deinit(name* self);                \
    type* name##_take(name* self);                 \
                                                   \
    int name##_push(name* self, type val);         \
    type name##_pop(name* self);

LIST_DECLARE(list_char, char)

#endif
