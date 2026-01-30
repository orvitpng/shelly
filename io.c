#define ESC 0x1b
#define DEL 0x7f

/* UART is a simple serial communication standard.
 * QEMU kindly implements this for simple I/O in virtual machines. */
#define UART ((volatile unsigned char*)0x10000000)
#define UART_LSR 5

/* TODO: create a small memory allocator for buffering? */
#define BUF_LEN 16

static char buf[BUF_LEN];

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

#include "debug.c"

char* gets()
{
    char* p = buf;

    int i = 0;
    while (true) {
        char c = getc();

        if (c == DEL) {
            if (i > 0) {
                p--;
                i--;
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
        if (i == BUF_LEN - 1
            || c < 0x20 || c >= 0x7f)
            continue;

        *p++ = c;
        i++;

        putc(c);
    }

    *p = 0;
    putc('\n');

    return buf;
}
