	TEXT	strchr(SB), $0
	MOVBU	c+4(FP), R4
	MOVW	R1, R3

	BEQ	R4, l2

/*
 * char is not null
 */
l1:
	MOVBU	(R3), R1
	ADD	$1, R3
	BEQ	R1, ret
	BNE	R1,R4, l1
	JMP	rm1

/*
 * char is null
 * align to word
 */
l2:
	AND	$3,R3, R1
	BEQ	R1, l3
	MOVBU	(R3), R1
	ADD	$1, R3
	BNE	R1, l2
	JMP	rm1

l3:
	MOVW	$0xff000000, R6
	MOVW	$0x00ff0000, R7
	MOVW	$0x0000ff00, R8

l4:
	MOVW	(R3), R5
	ADD	$4, R3
	AND	$0xff, R5, R1
	BEQ	R1, b0
	AND	R8, R5, R1
	BEQ	R1, b1
	AND	R7, R5, R1
	BEQ	R1, b2
	AND	R6, R5, R1
	BNE	R1, l4

rm1:
	ADD	$-1,R3, R1
	JMP	ret

b2:
	ADD	$-2,R3, R1
	JMP	ret

b1:
	ADD	$-3,R3, R1
	JMP	ret

b0:
	ADD	$-4,R3, R1
	JMP	ret

ret:
	RET
