#include "mem.h"
#define ECALLTMP	WORD	$0x73

GLOBL stack(SB), $4096

TEXT _start(SB), $0
	MOVW $setSB(SB), R3
	MOVW $stack+0(SB), R2
	ADD $4096, R2, R2
	MOVW $89, R10
	MOVW $0, R11
	MOVW $0, R12
	MOVW $0, R13
	MOVW $1, R17
	ECALLTMP
	JAL R0,main+0(SB)
	RET

TEXT sbi_ecall(SB), $0
	MOVW R13, R17
	MOVW $0, R13
	ECALLTMP
	RET
