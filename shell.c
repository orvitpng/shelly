#include "bool.h"
#include "debug.h"
#include "io.h"

void _start(void)
{
    puts("Say hello to my little shell!\n");

    while (true) {
        puts("# ");

        char* str = gets();
        if (!str)
            printf("gets errored!\n");
        else
            printf("%p: %s\n", str, str);
    }
}
