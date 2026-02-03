# 1 "link.ld.S"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 386 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "link.ld.S" 2
# 1 "include/def.S" 1
# 2 "link.ld.S" 2
# 1 "arch/riscv32/include/arch/def.S" 1
# 3 "link.ld.S" 2

ENTRY(_start)

SECTIONS {
    .text : { *(.text.init) *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }

 . = ALIGN(4);
    __bss = .;
    .bss : { *(.bss*) }
    __bss_end = .;

    . = ALIGN(16);
    . += 0x1000;
    __stack = .;

    . = ALIGN(4096);
    __heap = .;
    . += 0x10000;
    __heap_end = .;
}
