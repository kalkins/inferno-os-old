#include "mem.h"

GLOBL stack(SB), $4096

TEXT _start(SB), $-4
	/* set static base */
	MOVW $setSB(SB), R29

	/* set stack pointer */
	MOVW $stack(SB), R2
	ADD $4096, R2, R2

	/* clear bss */
	/*
	MOVW	$edata(SB), R5
	MOVW	$end(SB), R6
	MOVW	R0, 0(R5)
	ADD	$4, R5
	BLE	R6, R5, -2(PC)
	*/

	/* call main */
	JAL R0,main(SB)
end:
	ADD R0, R0, R0
	JMP end
	RET

TEXT sbi_ecall(SB), 1, $0
	/* The first argument is already in R10, the rest are one the stack */
	MOVW 4(FP), R11
	MOVW 8(FP), R12
	MOVW 12(FP), R17
	ECALL
	RET

TEXT setlabel(SB), $-4
	MOVW R1, 0(R10)
	//MOVW PC, 4(R10)
	MOVW $0, R10
	RET

TEXT gotolabel(SB), $-4
	MOVW 0(R10), R13
	//MOVW 4(R10), PC
	MOVW $1, R10
	RET

TEXT getcallerpc(SB), $-4
	MOVW R1, R10
	RET
