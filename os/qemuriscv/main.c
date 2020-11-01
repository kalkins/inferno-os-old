#include "u.h"
#include "../port/lib.h"
#include "dat.h"
#include "mem.h"
#include "fns.h"

Conf conf;
Mach *m = (Mach*)MACHADDR;
Proc *up = 0;

extern int main_pool_pcnt;
extern int heap_pool_pcnt;
extern int image_pool_pcnt;

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

static inline void sbi_ecall_console_write(const char *str)
{
	while (str && *str)
		sbi_ecall_console_putc(*str++);
}

static inline void sbi_ecall_console_serwrite(const char *str, int len)
{
	int i;
	for (i = 0; i < len; i++)
		sbi_ecall_console_putc(str[i]);
}

int     waserror(void) { return 0; }
extern int     splhi(void);
extern void    splx(int);
extern int     spllo(void);
extern void    splxpc(int);
extern int     islo(void);
extern int     setlabel(Label*);
extern void    gotolabel(Label*);
extern ulong   getcallerpc(void*);
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
confinit(void)
{
	ulong base;
	conf.topofmem = 128*MB;

	base = PGROUND((ulong)end);
	conf.base0 = base;

	conf.npage1 = 0;
	conf.npage0 = (conf.topofmem - base)/BY2PG;
	conf.npage = conf.npage0 + conf.npage1;
	conf.ialloc = (((conf.npage*(main_pool_pcnt))/100)/2)*BY2PG;

	conf.nproc = 100 + ((conf.npage*BY2PG)/MB)*5;
	conf.nmach = 1;

	print("Conf: top=%lud, npage0=%lud, ialloc=%lud, nproc=%lud\n",
			conf.topofmem, conf.npage0,
			conf.ialloc, conf.nproc);
}

static void
poolsizeinit(void)
{
	ulong nb;
	nb = conf.npage*BY2PG;
	poolsize(mainmem, (nb*main_pool_pcnt)/100, 0);
	poolsize(heapmem, (nb*heap_pool_pcnt)/100, 0);
	poolsize(imagmem, (nb*image_pool_pcnt)/100, 1);
}

void
main() {
	sbi_ecall_console_write("\nInferno is running!\n");

	memset(edata, 0, end-edata);
	memset(m, 0, sizeof(Mach));
	conf.nmach = 1;
	serwrite = &sbi_ecall_console_serwrite;

	confinit();
	xinit();
	poolinit();
	poolsizeinit();
}
