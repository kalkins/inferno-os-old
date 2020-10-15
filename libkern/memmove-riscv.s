TEXT	memcpy(SB), $0
TEXT	memmove(SB), $-4
	MOVW	R1, s1+0(FP)

	MOVW	n+8(FP), R2	/* count */
	BEQ	R2, return
	BGT	R2, ok
	MOVW	$0, R2
ok:
	MOVW	s1+0(FP), R4	/* dest pointer */
	MOVW	s2+4(FP), R3	/* source pointer */

	BLTU	R3, R4, back

/*
 * byte-at-a-time forward copy to
 * get source (R3) aligned.
 */
f1:
	AND	$3, R3, R1
	BEQ	R1, f2
	SUB	$1, R2
	BLT	R2, return
	MOVB	(R3), R1
	MOVB	R1, (R4)
	ADD	$1, R3
	ADD	$1, R4
	JMP	f1

/*
 * check that dest is aligned
 * if not, just go byte-at-a-time
 */
f2:
	AND	$3, R4, R1
	BEQ	R1, f3
	SUB	$1, R2
	BLT	R2, return
	JMP	f5
/*
 * quad-long-at-a-time forward copy
 */
f3:
	SUB	$16, R2
	BLT	R2, f4
	MOVW	0(R3), R5
	MOVW	4(R3), R6
	MOVW	8(R3), R7
	MOVW	12(R3), R8
	MOVW	R5, 0(R4)
	MOVW	R6, 4(R4)
	MOVW	R7, 8(R4)
	MOVW	R8, 12(R4)
	ADD	$16, R3
	ADD	$16, R4
	JMP	f3

/*
 * cleanup byte-at-a-time
 */
f4:
	ADD	$15, R2
	BLT	R2, return
f5:
	MOVB	(R3), R1
	MOVB	R1, (R4)
	ADD	$1, R3
	ADD	$1, R4
	SUB	$1, R2
	BGE	R2, f5
	JMP	return

return:
	MOVW	s1+0(FP),R0
	RET

/*
 * everything the same, but
 * copy backwards
 */
back:
	ADD	R2, R3
	ADD	R2, R4

/*
 * byte-at-a-time backward copy to
 * get source (R3) aligned.
 */
b1:
	AND	$3, R3, R1
	BEQ	R1, b2
	SUB	$1, R2
	BLT	R2, return
	SUB	$1, R3
	SUB	$1, R4
	MOVB	(R3), R1
	MOVB	R1, (R4)
	JMP	b1

/*
 * check that dest is aligned
 * if not, just go byte-at-a-time
 */
b2:
	AND	$3, R4, R1
	BEQ	R1, b3
	SUB	$1, R2
	BLT	R2, return
	JMP	b5
/*
 * quad-long-at-a-time backward copy
 */
b3:
	SUB	$16, R2
	BLT	R2, b4
	SUB	$16, R3
	SUB	$16, R4
	MOVW	0(R3), R5
	MOVW	4(R3), R6
	MOVW	8(R3), R7
	MOVW	12(R3), R8
	MOVW	R5, 0(R4)
	MOVW	R6, 4(R4)
	MOVW	R7, 8(R4)
	MOVW	R8, 12(R4)
	JMP	b3

/*
 * cleanup byte-at-a-time backward
 */
b4:
	ADD	$15, R2
	BLT	R2, return
b5:
	SUB	$1, R3
	SUB	$1, R4
	MOVB	(R3), R1
	MOVB	R1, (R4)
	SUB	$1, R2
	BGE	R2, b5
	JMP	return
