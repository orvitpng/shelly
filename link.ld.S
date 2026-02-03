#include <def.S>
#include <arch/def.S>

ENTRY(_start)

SECTIONS {
    .text : { *(.text.init) *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }

	. = ALIGN(4);
    __bss = .;
    .bss : { *(.bss*) }
    __bss_end = .;

    . = ALIGN(STACK_ALIGN);
    . += 0x1000;
    __stack = .;

    . = ALIGN(PAGE_SIZE);
    __heap = .;
    . += 0x10000;
    __heap_end = .;
}
