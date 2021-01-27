#include "u.h"
#include "../port/lib.h"
#include "dat.h"
#include "mem.h"
#include "fns.h"
#include "uart.h"
#include "debug.h"
#include "sbi.h"
#include "version.h"

Conf conf;
Mach *m = (Mach*)MACHADDR;
Proc *up = 0;

extern int main_pool_pcnt;
extern int heap_pool_pcnt;
extern int image_pool_pcnt;

int     segflush(void*, ulong) { return 0; }
void    idlehands(void) { return; }

void    setpanic(void) { return; }

void
exit(int panic)
{
	if (panic) {
		print("PANIC\n");
	}

	SBI_SHUTDOWN();
}

void
reboot(void)
{
	// Don't know how to talk to QEMU, but illegal write does the trick
	spllo();
	print("Rebooting\n");
	(*(volatile unsigned char*)(0x0000)) = 1;
}

void
halt(void)
{
	spllo();
	print("cpu halted\n");
	while (0) {}
}

Timer*  addclock0link(void (*)(void), int) { return 0; }
void    clockcheck(void) { return; }

void    fpinit(void) {}
void    FPsave(void*) {}
void    FPrestore(void*) {}

void
confinit(void)
{
	ulong base;
	conf.topofmem = 64*MiB + RAMZERO;
	DBGUVAR("conf.topofmem", conf.topofmem);

	base = PGROUND((ulong)end + 16*KiB);
	conf.base0 = base;

	conf.npage1 = 0;
	conf.npage0 = (conf.topofmem - base)/BY2PG;
	conf.npage = conf.npage0 + conf.npage1;
	conf.ialloc = (((conf.npage*(main_pool_pcnt))/100)/2)*BY2PG;

	conf.nproc = 100 + ((conf.npage*BY2PG)/MB)*5;
	conf.nmach = 1;

	/*
	DBGUVAR("end", (ulong) end);
	DBGUVAR("conf.base0", conf.base0);
	DBGUVAR("conf.npage1", conf.npage1);
	DBGUVAR("conf.npage0", conf.npage0);
	DBGUVAR("conf.npage", conf.npage);
	DBGUVAR("conf.ialloc", conf.ialloc);
	DBGUVAR("conf.nproc", conf.nproc);
	DBGUVAR("conf.nmach", conf.nmach);
	*/
	print("end 0x%08lux\n", (ulong) end);
	print("conf.base0 0x%08lux\n", conf.base0);
	print("conf.npage1 0x%08lux\n", conf.npage1);
	print("conf.npage0 0x%08lux\n", conf.npage0);
	print("conf.npage 0x%08lux\n", conf.npage);
	print("conf.ialloc 0x%08lux\n", conf.ialloc);
	print("conf.nproc 0x%08lux\n", conf.nproc);
	print("conf.nmach 0x%08lux\n", conf.nmach);

	print("Conf: top=0x%lux, npage0=0x%lux, ialloc=0x%lux, nproc=0x%lux\n",
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
init0(void)
{
	Osenv *o;
	char buf[2*KNAMELEN];

	up->nerrlab = 0;

	print("Starting init0()\n");
	spllo();

	if(waserror())
		panic("init0 %r");

	o = up->env;
	o->pgrp->slash = namec("#/", Atodir, 0, 0);
	cnameclose(o->pgrp->slash->name);
	o->pgrp->slash->name = newcname("/");
	o->pgrp->dot = cclone(o->pgrp->slash);

	chandevinit();

	if(!waserror()){
		ksetenv("cputype", "riscv", 0);
		snprint(buf, sizeof(buf), "riscv %s", conffile);
		ksetenv("terminal", buf, 0);
		poperror();
	}

	poperror();

	disinit("/osinit.dis");
}

void
userinit(void)
{
	Proc *p;
	Osenv *o;

	p = newproc();
	o = p->env;

	o->fgrp = newfgrp(nil);
	o->pgrp = newpgrp();
	o->egrp = newegrp();
	kstrdup(&o->user, eve);

	strcpy(p->text, "interp");

	p->fpstate = FPINIT;

	p->sched.pc = (ulong)init0;
	p->sched.sp = (ulong)p->kstack+KSTACK-8;

	ready(p);
}

void
alloctest() {
	ulong *a, *b, *c;
	char *d, *e;
	void *s;

	a = smalloc(4);
	print("Allocated a at addr 0x%p\n", a);
	b = smalloc(sizeof(ulong));
	print("Allocated b at addr 0x%p\n", b);
	s = smalloc(256);
	print("Allocated s at addr 0x%p\n", s);
	c = smalloc(sizeof(ulong));
	print("Allocated c at addr 0x%p\n", c);
	d = smalloc(sizeof(char));
	print("Allocated d at addr 0x%p\n", d);
	e = smalloc(sizeof(char));
	print("Allocated e at addr 0x%p\n", e);
}

void
main() {
	char input;

	uartsetup();
	serwrite = &uartputs;

	memset(edata, 0, end-edata);
	memset(m, 0, sizeof(Mach));
	conf.nmach = 1;

	print("\nWelcome to Inferno!\n");

	while(1) {
		print("\nEnter 'd' to toggle debug mode, and 'c' to start Inferno: ");
		input = uartgetc();

		if (input == 'c') {
			print("\nStarting Inferno\n\n");
			break;
		} else if (input == 'd') {
			DBG_IF {
				DBG_DISABLE();
				print("\nDebug mode is off\n");
			} else {
				DBG_ENABLE();
				print("\nDebug mode is on\n");
			}
		} else {
			print("\nInvalid input: %d\n", input);
		}
	}

	confinit();
	xinit();
	poolinit();
	poolsizeinit();
	trapinit();
	printinit();

	print("\nRISC-V QEMU\n");
	print("Inferno OS %s Vita Nuova\n\n", VERSION);

	DBG("procinit()");
	procinit();
	DBG("links()");
	links();
	DBG("chandevreset()");
	chandevreset();

	DBG("eve");
	eve = strdup("inferno");

	DBG("userinit()");
	userinit();
	DBG("schedinit()");
	schedinit();

	halt();
}
