#include <arch/asm.h>

.section	.text

.global		_main
_main:		auipc	t0,		0
			la		t1,		__reloc_start
			la		t2,		__reloc_end
			beq		t1,		t2,				1f

0:			L	    t3,		0 * Z(t1)
			L   	t4,		1 * Z(t1)
			L   	t5,		2 * Z(t1)
			addi	t1,		t1,				3 * Z

			andi	t4,		t4,				0xff
			li		t6,		3
			bne		t4,		t6,				0b

			add		t3,		t3,				t0
			add		t5,		t5,				t0
			S   	t5,		0 * Z(t3)
			bne		t1,		t2,				0b

1:			la		t0,		__bss_start
			la		t1,		__bss_end
			beq		t0,		t1,				1f

0:			S   	zero,	0 * Z(t0)
			addi	t0,		t0,				Z
			bne		t0,		t1,				0b

1:			la		sp,		__stack_end
			j		main

.global		_park
_park:		wfi
			j		_park
