#include <def.inc>
#include <arch/def.inc>

ENTRY(_start)

SECTIONS {
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
    . += 0x1000;
    __stack_end = .;

    . = ALIGN(PAGE_SIZE);
    __heap_start = .;
    . += 0x10000;
    __heap_end = .;
}
