#define IOBASE 0x10001000

/*
 * Trap codes.
 *
 * Interrupts (IRQ) have MSB set to 1.
 *
 * The letter following IRQ specifies if it is for
 * supervisor mode (S) or user mode (U).
 *
 * Most other traps are errors, except UCALL and SCALL,
 * which are environment calls.
 */
#define IRQUSoftware		(0 | 1<<31)
#define IRQSSoftware		(1 | 1<<31)
#define IRQUTimer			(4 | 1<<31)
#define IRQSTimer			(5 | 1<<31)
#define IRQUExternal		(8 | 1<<31)
#define IRQSExternal		(9 | 1<<31)
#define ERRInstrMisaligned	0
#define ERRInstrAccess		1
#define ERRInstrIllegal		2
#define ERRBreakpoint		3
#define ERRLoadMisaligned	4
#define ERRLoadAccess		5
#define ERRStoreMisaligned	6
#define ERRStoreAccess		7
#define ERRInstrPageFault	12
#define ERRLoadPageFault	13
#define ERRStorePageFault	15
#define UCALL				8
#define SCALL				9
