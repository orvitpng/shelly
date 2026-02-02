SECTIONS {
    . = 0x80000000;

    .text : {
        *(.text.init)
        *(.text*)
    }

    . = ALIGN(16);
    . += 0x1000;
    __stack = .;

    __heap = .;
    . += 0x10000;
    __heap_end = .;
}
