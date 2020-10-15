#define EBREAK	WORD	$(0x73 | 1<<20)
TEXT	_mulv(SB), $0
	MOVW	4(FP), R2	// x.lo
	MOVW	8(FP), R3	// x.hi
	MOVW	12(FP), R4	// y.lo
	MOVW	16(FP), R5	// y.hi
	MULHU	R4, R2, R7	// (x.lo*y.lo).hi
	MUL	R4, R2, R6	// (x.lo*y.lo).lo
	MUL	R3, R4, R8	// (x.hi*y.lo).lo
	ADD	R8, R7
	MUL	R2, R5, R8	// (x.lo*y.hi).lo
	ADD	R8, R7
	MOVW	R6, 0(R1)
	MOVW	R7, 4(R1)
	RET
