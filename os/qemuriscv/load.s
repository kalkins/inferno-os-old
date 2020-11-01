#include "mem.h"

GLOBL stack(SB), $4096

TEXT _start(SB), $-4
	/* set static base */
	MOVW $setSB(SB), R3

	/* set stack pointer */
	MOVW $stack(SB), R2
	ADD $4096, R2, R2

	/* clear bss */
	MOVW	$edata(SB), R4
	MOVW	$end(SB), R5
bssloop:
	MOVW	R0, 0(R4)
	ADD	$4, R4
	BLE	R5, R4, bssloop

	/* call main */
	JAL R1, main(SB)
deadloop:
	ADD R0, R0, R0
	JMP deadloop
	RET

TEXT sbi_ecall(SB), 1, $-4
	/* The first argument is already in R10, the rest are one the stack */
	MOVW R8, R10
	MOVW 4(FP), R11
	MOVW 8(FP), R12
	MOVW 12(FP), R17
	ECALL
	MOVW R10, R8
	RET

TEXT setlabel(SB), $-4
	MOVW R1, 0(R8) // Save the link register (calling address) to the first field
	MOVW R2, 4(R8) // Save the stack pointer to the second field
	MOVW $0, R8    // Return 0
	RET

TEXT gotolabel(SB), $-4
	MOVW 0(R8), R4 // Get the address from the first field
	MOVW 4(R8), R2 // Get the stack pointer
	JAL R1, 0(R4)  // Jump to the address
	MOVW $1, R8    // (After the label returns) return 1
	RET

TEXT getcallerpc(SB), $-4
	MOVW R1, R8
	RET

TEXT splhi(SB), $-4
	MOVW $(MACHADDR), R4
	MOVW R1, 0(R4)
	MOVW $0, CSR(0x104)
	RET

TEXT spllo(SB), $-4
	MOVW $-1, R4
	MOVW R4, CSR(0x104)
	RET

TEXT splx(SB), $-4
	MOVW $(MACHADDR), R4
	MOVW R1, 0(R4)
TEXT splxpc(SB), $-4
	MOVW R8, CSR(0x104)
	RET

TEXT islo(SB), $-4
	MOVW CSR(0x104), R8
	RET
