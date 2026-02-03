#include <stdbool.h>

[[noreturn]] void main()
{
    *(volatile char*)0x10000000 = 'A';
    while (true)
        ;
}
