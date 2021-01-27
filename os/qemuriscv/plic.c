#include "plic.h"
#include "io.h"
#include "mem.h"

void
plicinit(void)
{
	*(long*)(PLIC_BASE + PLICUART*4) = 1;
	*(long*)(PLIC_SENABLE) = (1<<PLICUART);
	*(long*)(PLIC_SPRIORITY) = 0;
}

long
plicclaim(void)
{
	return *(long*) PLIC_SCLAIM;
}

void
plic_complete(long irq)
{
	*(long*) PLIC_SCLAIM = irq;
}
