#include "bool.h"
#include "list.h"

#define ESC 0x1b
#define DEL 0x7f

/* UART is a simple serial communication standard.
 * QEMU kindly implements this for simple I/O in virtual machines. */
#define UART ((volatile unsigned char*)0x10000000)
#define UART_LSR 5

void putc(char c) { UART[0] = c; }

char getc()
{
    while (!(UART[UART_LSR] & true))
        ;
    return UART[0];
}

void puts(const char* str)
{
    while (*str)
        putc(*str++);
}

char* gets()
{
    list_char buf = list_char_empty;

    while (true) {
        char c = getc();

        if (c == DEL) {
            if (buf.len > 0) {
                buf.len--;
                puts("\b \b");
            }
            continue;
        }

        if (c == ESC) {
            /* TODO: handle certain escale sequences instead of ignoring */
            getc();
            getc();
            continue;
        }

        if (c == '\r')
            break;
        if (c < 0x20 || c >= 0x7f)
            continue;

        if (!list_char_push(&buf, c)) {
            list_char_deinit(&buf);
            return 0;
        }

        putc(c);
    }

    list_char_push(&buf, '\0');
    putc('\n');

    return list_char_take(&buf);
}
