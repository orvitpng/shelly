.section    .text.init                  # tell the linker to load this first

            la      sp,     __stack     # load stack top into stack pointer
            call    _start              # call main function (C code)
1:          wfi                         # wait for interrupt (halt the core)
            j       1b                  # loop back (wfi can wake spuriously)
