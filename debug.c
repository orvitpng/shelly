#include "io.h"

#define VIRT_TEST ((volatile unsigned int*)0x100000)
#define VIRT_TEST_FAIL 0x3333

#define va(ap, type) __builtin_va_arg(ap, type)

static const char hex[] = "0123456789abcdef";

/* qemu-specific panic/exit */
void panic(const char* msg)
{
    puts("panic: ");
    puts(msg);
    putc('\n');

    *VIRT_TEST = VIRT_TEST_FAIL;
    __builtin_unreachable();
}

/* TODO: add more/finish more specifiers */
void printf(const char* fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            putc(*fmt++);
            continue;
        }

        fmt++;
        switch (*fmt++) {
        case 'c':
            putc(va(ap, int));
            break;
        case 'x': {
            unsigned char c = va(ap, int);
            putc(hex[c >> 4]);
            putc(hex[c & 0x0f]);
        }; break;
        case 'p': {
            unsigned long ptr = (unsigned long)va(ap, void*);
            for (int i = sizeof(ptr) * 2 - 1; i != 0; i--)
                putc(hex[ptr >> i * 4 & 0xf]);
        }; break;
        case 's': {
            const char* str = va(ap, const char*);
            while (*str)
                putc(*str++);
        }; break;
        default:
            panic("invalid format");
        }
    }

    __builtin_va_end(ap);
}
