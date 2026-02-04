#include <heap.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>

#define UART *(volatile uint8_t*)0x10000000

noreturn void main()
{
    uint8_t* ptr = alloc(5);
    ptr[0] = 'H';
    ptr[1] = 'i';
    ptr[2] = '!';
    ptr[3] = '\n';
    ptr[4] = '\0';

    while (*ptr)
        UART = *ptr++;

    while (true)
        ;
}
