	TEXT	memset(SB),$12
MOVW R1, s1+0(FP)

	MOVW	n+8(FP), R3		/* R3 is count */
	MOVW	p+0(FP), R4		/* R4 is pointer */
	MOVW	c+4(FP), R5		/* R5 is char */
	ADD	R3,R4, R6		/* R6 is end pointer */

/*
 * if not at least 4 chars,
 * dont even mess around.
 * 3 chars to guarantee any
 * rounding up to a word
 * boundary and 4 characters
 * to get at least maybe one
 * full word store.
 */
	SLT	$4,R3, R1
	BNE	R1, out

/*
 * turn R5 into a word of characters
 */
	AND	$0xff, R5
	SLL	$8,R5, R1
	OR	R1, R5
	SLL	$16,R5, R1
	OR	R1, R5

/*
 * store one byte at a time until pointer
 * is aligned on a word boundary
 */
l1:
	AND	$3,R4, R1
	BEQ	R1, l2
	MOVB	R5, 0(R4)
	ADD	$1, R4
	JMP	l1

/*
 * turn R3 into end pointer-15
 * store 16 at a time while theres room
 */
l2:
	ADD	$-15,R6, R3
l3:
	SLTU	R3,R4, R1
	BEQ	R1, l4
	MOVW	R5, 0(R4)
	MOVW	R5, 4(R4)
	ADD	$16, R4
	MOVW	R5, -8(R4)
	MOVW	R5, -4(R4)
	JMP	l3

/*
 * turn R3 into end pointer-3
 * store 4 at a time while theres room
 */
l4:
	ADD	$-3,R6, R3
l5:
	SLTU	R3,R4, R1
	BEQ	R1, out
	MOVW	R5, 0(R4)
	ADD	$4, R4
	JMP	l5

/*
 * last loop, store byte at a time
 */
out:
	SLTU	R6,R4 ,R1
	BEQ	R1, ret
	MOVB	R5, 0(R4)
	ADD	$1, R4
	JMP	out

ret:
	MOVW	s1+0(FP), R1
	RET
	END
