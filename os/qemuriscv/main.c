#include "u.h"
#include "../port/lib.h"
#include "dat.h"
#include "mem.h"

Conf conf;
Mach *m = (Mach*)MACHADDR;
Proc *up = 0;

#include "../port/uart.h"
PhysUart* physuart[1];

#include <sbi/sbi_ecall_interface.h>

extern int sbi_ecall(unsigned long a0, unsigned long a1, unsigned long a2, unsigned long num);

#define SBI_ECALL(__num, __a0, __a1, __a2) sbi_ecall(__a0, __a1, __a2, __num)
	/*
	({                                                                    \
		register unsigned long a0 asm("a0") = (unsigned long)(__a0);  \
		register unsigned long a1 asm("a1") = (unsigned long)(__a1);  \
		register unsigned long a2 asm("a2") = (unsigned long)(__a2);  \
		register unsigned long a7 asm("a7") = (unsigned long)(__num); \
		asm volatile("ecall"                                          \
			     : "+r"(a0)                                       \
			     : "r"(a1), "r"(a2), "r"(a7)                      \
			     : "memory");                                     \
		a0;                                                           \
	})
	*/

#define SBI_ECALL_0(__num) SBI_ECALL(__num, 0, 0, 0)
#define SBI_ECALL_1(__num, __a0) SBI_ECALL(__num, __a0, 0, 0)
#define SBI_ECALL_2(__num, __a0, __a1) SBI_ECALL(__num, __a0, __a1, 0)

#define sbi_ecall_console_putc(c) SBI_ECALL_1(SBI_EXT_0_1_CONSOLE_PUTCHAR, (c))

static inline void sbi_ecall_console_puts(const char *str)
{
	while (str && *str)
		sbi_ecall_console_putc(*str++);
}

int     waserror(void) { return 0; }
int     splhi(void) { return 0; }
void    splx(int) { return; }
int     spllo(void) { return 0; }
void    splxpc(int) { return; }
int     islo(void) { return 0; }
int     setlabel(Label*) { return 0; }
void    gotolabel(Label*) { return; }
ulong   getcallerpc(void*) { return 0; }
int     segflush(void*, ulong) { return 0; }
void    idlehands(void) { return; }
void    kprocchild(Proc *p, void (*func)(void*), void *arg) { return; }
ulong   _tas(ulong*) { return 0; }
ulong   _div(ulong*) { return 0; }
ulong   _divu(ulong*) { return 0; }
ulong   _mod(ulong*) { return 0; }
ulong   _modu(ulong*) { return 0; }

void    setpanic(void) { return; }
void    dumpstack(void) { return; }
void    exit(int) { return; }
void    reboot(void) { return; }
void    halt(void) { return; }

Timer*  addclock0link(void (*)(void), int) { return 0; }
void    clockcheck(void) { return; }

void    fpinit(void) {}
void    FPsave(void*) {}
void    FPrestore(void*) {}

void
main() {
	sbi_ecall_console_puts("\nTest payload running\n");
	for (;;);
}
