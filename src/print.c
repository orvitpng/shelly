// completely written by ai for now. i simply couldn't be bothered to writte an
// actual implementation until i get io figured out. this will be removed in its
// entirety once i figure that out

#include <stdarg.h>
#include <stdint.h>

#define UART *(volatile uint8_t*)0x10000000

static void uart_putc(char c)
{
    UART = c;
}

static void uart_puts(const char* s)
{
    while (*s)
        uart_putc(*s++);
}

static void uart_putx(unsigned int v)
{
    for (int i = 28; i >= 0; i -= 4)
        uart_putc("0123456789abcdef"[(v >> i) & 0xf]);
}

static void uart_putd(int v)
{
    char buf[12];
    int i = 0;
    unsigned int u;

    if (v < 0) {
        uart_putc('-');
        u = -v;
    } else {
        u = v;
    }

    do {
        buf[i++] = '0' + u % 10;
        u /= 10;
    } while (u);

    while (i--)
        uart_putc(buf[i]);
}

void printf(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            uart_putc(*fmt);
            continue;
        }
        switch (*++fmt) {
        case 'c':
            uart_putc(va_arg(ap, int));
            break;
        case 's':
            uart_puts(va_arg(ap, const char*));
            break;
        case 'd':
            uart_putd(va_arg(ap, int));
            break;
        case 'x':
            uart_putx(va_arg(ap, unsigned int));
            break;
        case '%':
            uart_putc('%');
            break;
        default:
            uart_putc('%');
            uart_putc(*fmt);
            break;
        }
    }

    va_end(ap);
}
