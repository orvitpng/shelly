.section	.text.init
.global		_start

_start:		csrr	t0,		mhartid
			beqz	t0,		init
1:			wfi
			j		1b

init:		lla		sp,		__stack
			lla		t0,		__bss
			lla		t1,		__bss_end

1:			beq	    t0,		t1,			main
			sw		zero,	0(t0)
			addi	t0,		t0,			4
			j		1b
