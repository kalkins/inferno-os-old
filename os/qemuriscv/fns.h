#define KADDR(p) ((void*) p)
#define PADDR(p) ((ulong) p)
#define coherence()     /* nothing needed for uniprocessor */
#define procsave(p)     /* Save the mach part of the current */
						/* process state, no need for one cpu */

void (*screenputs)(char*, int);

#include "../port/portfns.h"

#define	waserror()	(up->nerrlab++, setlabel(&up->errlab[up->nerrlab-1]))

int inb(ulong);
int ins(ulong);
ulong inl(ulong);
void outb(ulong, int);
void outs(ulong, int);
void outl(ulong, ulong);
void inss(ulong, void*, int);
void outss(ulong, void*, int);
void insb(ulong, void*, int);
void outsb(ulong, void*, int);

void delay(int);
void trapinit(void);
char *trapname(long scause);
void links(void);
int isvalid_wa(void*);
int isvalid_va(void*);
void dumpregs(Ureg* ureg);
