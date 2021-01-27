#include "u.h"
#include "ureg.h"
#include "../port/lib.h"
#include "dat.h"
#include "fns.h"
#include "csr.h"
#include "mem.h"
#include "io.h"
#include "plic.h"
#include "uart.h"
#include "debug.h"

#define TRAP_MODE_DIRECT	0
#define TRAP_MODE_VECTORED	1

#define INTR_USOFTWARE	(1<<0)
#define INTR_SSOFTWARE	(1<<1)
#define INTR_UTIMER		(1<<4)
#define INTR_STIMER		(1<<5)
#define INTR_UEXTERNAL	(1<<8)
#define INTR_SEXTERNAL	(1<<9)

#define INTR_ALL		(INTR_USOFTWARE | INTR_SSOFTWARE | INTR_UTIMER \
		 				| INTR_STIMER | INTR_UEXTERNAL | INTR_SEXTERNAL)

extern void traphandler(void);

int in_error_trap = 0;

void
devinterrupt(void)
{
	long irq = plicclaim();

	switch(irq) {
	case PLICUART:
		DBG("UART interrupt\n");
		uartintr();
		break;
	default:
		print("WARNING: Unknown PLIC interrupt %ld", irq);
	}

	if (irq) {
		plic_complete(irq);
	}
}

// This is called by the assembly traphandler after registers are saved,
// with an Ureg representing the state when the trap occured.
// It should return normally, traphandler handles SRET
void
kerneltrap(Ureg *ureg)
{
	long cause = csr_read_scause();
	long status = csr_read_sstatus();
	long pending = csr_read_sip();
	ulong epc = csr_read_sepc();
	ulong tval = csr_read_stval();

	DBG_IF {
		print("TRAP: %s\n", trapname(cause));
	}

	switch (cause) {
	case IRQUSoftware:
		break;
	case IRQSSoftware:
		break;
	case IRQUTimer:
		break;
	case IRQSTimer:
		break;
	case IRQUExternal:
		devinterrupt();
		break;
	case IRQSExternal:
		devinterrupt();
		break;
	default:
		print("ERROR: 0x%lux=0x%lux: %s\n", epc, tval, trapname(cause));
		if (in_error_trap == 1) {
			print("Happened while handling another error\n");
			print("Stalling...\n");
		} else {
			in_error_trap = 1;
			print("Dumping regs and stack\n");
			dumpregs(ureg);
		}
		for (;;) {}
		panic("Unhandled trap");
	}

	// Clear pending interrupts
	csr_clear_sip(pending);

	// Restore trap registers, in case traps happened during this function
	csr_write_sepc(epc);
	csr_write_sstatus(status);
}

void
trapinit(void)
{
	// Set trap handler
	// This produces the warning "address of array/func ignored", but it works fine
	ulong handler_addr = (ulong) &traphandler;
	ulong intr_mask = (INTR_USOFTWARE | INTR_UTIMER | INTR_STIMER | INTR_UEXTERNAL | INTR_SEXTERNAL);

	if (handler_addr & 0x00000003) {
		// The compiler should make sure functions are aligned, but
		// just in case
		print("WARNING: traphandler not aligned. Rounding address down");
		handler_addr &= 0xfffffffc;
	}

	csr_write_stvec(handler_addr | TRAP_MODE_DIRECT);

	// Set sscratch to the trap stack location
	csr_set_sscratch(TRAPSTACK);

	// First make sure all interrupts are disabled, then enable those we want.
	csr_clear_sie(INTR_ALL);
	csr_set_sie(intr_mask);

	// Enable PLIC interrupts
	plicinit();

	// Enable interrupts globally
	spllo();
}

char*
trapname(long cause)
{
	switch (cause) {
	case IRQUSoftware:
		return "User software interrupt";
	case IRQSSoftware:
		return "Supervisor software interrupt";
	case IRQUTimer:
		return "User timer interrupt";
	case IRQSTimer:
		return "Supervisor timer interrupt";
	case IRQUExternal:
		return "User external interrupt";
	case IRQSExternal:
		return "Supervisor external interrupt";
	case ERRInstrMisaligned:
		return "Instruction misaligned";
	case ERRInstrAccess:
		return "Instruction access fault";
	case ERRInstrIllegal:
		return "Illegal instruction";
	case ERRBreakpoint:
		return "Breakpoint";
	case ERRLoadMisaligned:
		return "Load misaligned";
	case ERRLoadAccess:
		return "Load access fault";
	case ERRStoreMisaligned:
		return "Store misaligned";
	case ERRStoreAccess:
		return "Store access fault";
	case ERRInstrPageFault:
		return "Instruction page fault";
	case ERRLoadPageFault:
		return "Load page fault";
	case ERRStorePageFault:
		return "Store page fault";
	case UCALL:
		return "UCALL";
	case SCALL:
		return "SCALL";
	default:
		if (cause < 0){
			return "Unknown interrupt";
		} else {
			return "Unknown trap";
		}
	}
}

int
isvalid_va(void *v)
{
	return (ulong)v < conf.topofmem && (ulong)v > RAMZERO;
}

int
isvalid_wa(void *v)
{
	return isvalid_va(v) && !((ulong)v & 3);
}
