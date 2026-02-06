#include <def.h>
#include <arch/def.h>

ENTRY(_entry)

SECTIONS {
    __start = .;
	.blob :
	{
		*(.text.start)
		*(.text*)
		*(.rodata*)
		*(.data*)
	}

	.reloc :
	{
		__reloc_start = .;
		*(.rela*)
		__reloc_end = .;
	}

	.bss :
	{
		__bss_start = .;
		*(.bss*)
		__bss_end = .;
	}

    . = ALIGN(STACK_ALIGN);
    . += STACK_SIZE;
    __stack_end = .;

    . = ALIGN(PAGE_SIZE);
    __heap_start = .;
    . += HEAP_SIZE;
    __heap_end = .;
    __end = .;
}
