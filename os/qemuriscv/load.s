#include "mem.h"
#include "csrregs.h"

//GLOBL stack(SB), $KSTKSIZE

TEXT _start(SB), $-4
	/* set static base */
	MOVW $setSB(SB), R3

	/* set stack pointer */
	//MOVW $stack(SB), R2
	//ADD $4096, R2, R2
	MOVW $(MACHADDR+MACHSIZE-4), R2

	/* call main */
	JAL R1, main(SB)
deadloop:
	ADD R0, R0, R0
	JMP deadloop
	RET

TEXT sbi_ecall(SB), 1, $8
	/* The address of the struct to populate is in R8, the rest are on stack */
	MOVW R8, .ret+0(FP)

	/* Move the arguments and perform the call */
	MOVW a0+4(FP), R10
	MOVW a1+8(FP), R11
	MOVW a3+12(FP), R12
	MOVW num+16(FP), R17
	MOVW num+20(FP), R16
	ECALL

	/* Move the result from R10 and R11 to the result struct */
	MOVW .ret+0(FP), R8
	MOVW R10, 0(R8)
	MOVW R11, 4(R8)
	RET

TEXT setlabel(SB), $-4
	MOVW R2, 0(R8) // Save the stack pointer to the first field
	MOVW R1, 4(R8) // Save the link register (calling address) to the second field
	MOVW $0, R8    // Return 0
	RET

TEXT gotolabel(SB), $0
	MOVW 0(R8), R10 // Get the stack pointer
	MOVW 4(R8), R11 // Get the address

	MOVW R10, R2 // Get the stack pointer
	JAL R1, 0(R11)  // Jump to the address
	MOVW $1, R8    // (After the label returns) return 1
	RET

TEXT getcallerpc(SB), $-4
	MOVW 0(R2), R8
	RET

// Test-And-Set
TEXT _tas(SB), $-4
	MOVW $1, R9
	WORD $143926319 // AMOSWAP.W 0 0 R9 R8 R8
	RET

TEXT breakpoint(SB), $0
	MOVW R1, R8
	//ADDW $-4, R8, R8
	JAL R1, _breakpoint(SB)
	RET
