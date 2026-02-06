#include <arch/asm.h>

.section	.text.start

.global		_entry
_entry:		la			t0,			boot
			li			t1,			1
			amoswap.w	t1,			t1,			0(t0)
			bnez		t1,			_idle

			la			a0,			_start
			csrw		stvec,		a0
			csrw		mepc,		a0

			la			t1,			trap
			csrw		mtvec,		t0

			li			t0,			(1 << 11)		# MPP = 1 (S mode)
            li          t1,         0x1f            # R W X
            li          t2,         -1
			csrw		mstatus,	t0
            csrw        pmpcfg0,    t1
            csrw        pmpaddr0,   t2

			csrr		a0,			mhartid
            mret

trap:
.global		_idle
_idle:		wfi
			j			_idle

.section	.data

.align		A
boot:		N		0
