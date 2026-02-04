.section	.text.start
.global		_start

_start:		auipc		t0,		0
			la			t1,		__reloc_start
			la			t2,		__reloc_end
			beq			t1,		t2,				1f

0:			lw			t3,		0(t1)
			lw			t4,		4(t1)
			lw			t5,		8(t1)
			addi		t1,		t1,				12

			andi		t4,		t4,				0xff
			li			t6,		3
			bne			t4,		t6,				0b

			add			t3,		t3,				t0
			add			t5,		t5,				t0
			sw			t5,		0(t3)
			bne			t1,		t2,				0b

1:			la			t0,		__bss_start
			la			t1,		__bss_end
			beq			t0,		t1,				1f

0:			sw			zero,	0(t0)
			addi		t0,		t0,				4
			bne			t0,		t1,				0b

1:			la			sp,		__stack_end
			tail		main
