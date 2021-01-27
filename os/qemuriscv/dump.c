#include "u.h"
#include "ureg.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "debug.h"

void
dumplongs(char *msg, ulong *v, int n)
{
	int i, l, pad;

	l = 0;
	pad = strlen(msg) + 4;
	iprint("%s at %.8p: ", msg, v);
	for(i=0; i<n; i++){
		if(l >= 4){
			iprint("\n%*c%.8p: ", pad, ' ', v);
			l = 0;
		}
		if(isvalid_va(v)){
			iprint(" %.8lux", *v++);
			l++;
		}else{
			iprint(" invalid");
			break;
		}
	}
	iprint("\n");
}

void
dumparound(ulong addr)
{
	uint addr0 = (addr/16)*16;
	int a_row, a_col;
	uchar ch, *cha;
	uint c;
	/* +-32 bytes to print */
	print("%ux:\n", addr0 +(-2)*16);
	for (a_col = 0; a_col<16; ++a_col) {
		print("|%.2uX", a_col);
	}
	print("\n");

	for (a_row = -2; a_row < 3; ++a_row) {
		for (a_col = 0; a_col<16; ++a_col) {
			cha = (uchar *)(addr0 +a_row*16+a_col);
			ch = *cha;
			c = ch;
			if (cha == (uchar *)addr)
				print(">%2.2uX", c);
			else print(" %2.2uX", c);
		}
		print("\n");
	}
	print("\n");
}


static void
_dumpstack(Ureg *ureg)
{
	ulong *v, *l;
	ulong inst;
	ulong *estack;
	ulong *caller;
	ulong *callee;
	int i;

	l = (ulong*) ureg->sp;

	print("ktrace PC: 0x%lux SP: 0x%lux\n", ureg->pc, ureg->sp);
	if(up != nil && l >= (ulong*) up->kstack && l <= (ulong*)(up->kstack+KSTACK-4)) {
		estack = (ulong*) (up->kstack+KSTACK);
	} else if(l >= (ulong*) m->stack && l <= ((ulong*)m+BY2PG-4)) {
		estack = (ulong*) m+BY2PG-4;
	} else if(l <= (ulong*) TRAPSTACK && l >= (ulong*) TRAPSTACK - KSTACK) {
		print("Stacktrace in trap handler\n");
		estack = (ulong*) TRAPSTACK;
	} else {
		iprint("unknown stack\n");
		return;
	}

	print("Searching stack 0x%lux-0x%lux\n", l, estack);

	i = 0;
	while(l<estack) {
		// The link is stored at 0(R2).
		// TODO: Figure out what to do for leaf functions
		caller = ((ulong*) (*l)) - 1;
		DBG_IF { print("stack:  0x%p\n", l); }
		DBG_IF { print("caller: 0x%p\n", caller); }

		if (!((ulong) caller > RAMZERO && caller < (ulong*) 0xffffffff)) {
			print("Illegal link address 0x%p\n", caller);
			print("Aborting stack trace\n");
			break;
		}

		inst = *caller;
		DBG_IF { print("JAL inst: 0x%08lux\n", inst); }

		int isjal;
		int isadd;
		long addimm;
		long jaloff;
		ulong jaladdr;

		if ((inst & 0x007f) == 0x6f) {
			// Normal JAL
			// Load the jump offset
			jaloff  = (inst & 0x000ff000) >> 0;  // imm[19:12]
			jaloff |= (inst & 0x00100000) >> 9;  // imm[11]
			jaloff |= (inst & 0x7fe00000) >> 20; // imm[10:1]

			// Sign extend
			if (inst & (1<<31)) {
				jaloff |= 0xfff00000;
			}
		} else if ((inst & 0xe0070000) == 0x20050000) {
			// Compressed JAL
			inst = inst >> 16;

			jaloff  = (inst & 0x0004) << 3; // imm[5]
			jaloff |= (inst & 0x0038) >> 2; // imm[3:1]
			jaloff |= (inst & 0x0040) << 1; // imm[7]
			jaloff |= (inst & 0x0080) >> 1; // imm[6]
			jaloff |= (inst & 0x0100) << 2; // imm[10]
			jaloff |= (inst & 0x0600) >> 1; // imm[9:8]
			jaloff |= (inst & 0x0800) >> 7; // imm[4]

			// Sign extend
			if (inst & (1<<12)) {
				jaloff |= 0xfffff800;
			}

			// The caller address is incorrect, because the instruction was compressed,
			// so we compensate here
			jaloff += 2;
		} else {
			print("ERROR:\n");
			print("Instruction at link address 0x%p is not a JAL.\n", caller);
			print("The instruction was 0x%08lux\n", inst);
			dumplongs("caller", caller-12, 32);
			print("Aborting stack trace\n");
			break;
		}

		DBG_IF { print("The JAL offset is %ld\n", jaloff); }

		// The address of the jump
		callee = (ulong*) (((ulong) caller) + jaloff);

		DBG_IF { print("The callee address is 0x%08lux\n", callee); }

		inst = *callee;

		DBG_IF { print("ADDI inst: 0x%lux\n", inst); }

		// Check that the instruction is "ADD $x, R2, R2"
		if ((inst & 0x000fffff) == 0x10113) {
			// Normal ADDI with rd=R2
			addimm = (inst & 0xFFF00000) >> 20;

			// Sign extend
			if (addimm & (1<<11)) {
				addimm |= 0xfffff000;
			}
		} else if ((inst & 0xef83) == 0x0101) {
			// Compressed ADDI with rd=R2
			addimm = (inst & 0x7c) >> 2;

			// Sign extend
			if (inst & (1<<12)) {
				addimm |= 0xffffffe0;
			}
		} else {
			print("ERROR:\n");
			print("The first instruction in the function at 0x%p does not grow the stack.\n", callee);
			print("The instruction was 0x%08lux\n", inst);
			dumplongs("callee", callee-12, 32);
			print("Aborting stack trace\n");
			break;
		}

		print("0x%p called from 0x%p, using stack size %ld\n", callee, caller, addimm);

		if (addimm >= 0) {
			print("ERROR:\n");
			print("The stack is incremented, not decremented.\n");
			dumplongs("callee", callee-12, 32);
			print("Aborting stack trace\n");
			break;
		}

		// Increment the stack. l has to be cast back and forth to avoid pointer alignment.
		l =  (ulong*) (((ulong) l) - addimm);

		/*
		if(i == 4){
			iprint("\n");
			i = 0;
		}
		*/
	}
	if(i)
		print("\n");
}

/*
 * Fill in enough of Ureg to get a stack trace, and call a function.
 * Used by debugging interface rdb.
 */
void
callwithureg(void (*fn)(Ureg*))
{
	Ureg ureg;
	ureg.pc = getcallerpc(&fn);
	ureg.sp = (ulong)&fn;
	ureg.r1 = 0;
	fn(&ureg);
}

void
dumpstack(void)
{
	callwithureg(_dumpstack);
}

void
dumpregs(Ureg* ureg)
{
	print("Mode  0x%08lux   PC   0x%08lux   status  0x%08lux   cause    0x%08lux   tval  0x%08lux \n",
	      ureg->curmode, ureg->pc, ureg->status, ureg->cause, ureg->tval);
	print("R14   0x%08lux   R13  0x%08lux   R12     0x%08lux   R11      0x%08lux   R10   0x%08lux\n",
		ureg->r14, ureg->r13, ureg->r12, ureg->r11, ureg->r10);
	print("R9    0x%08lux   R8   0x%08lux   R7      0x%08lux   R6       0x%08lux   R5    0x%08lux\n",
		ureg->r9, ureg->r8, ureg->r7, ureg->r6, ureg->r5);
	print("R4    0x%08lux   R3   0x%08lux   R2/sp   0x%08lux   R1/link  0x%08lux\n",
		ureg->r4, ureg->r3, ureg->r2, ureg->r1);

	if(up)
		print("Process stack:  %8.8lux-%8.8lux\n",
			up->kstack, up->kstack+KSTACK-4);
	else
		print("System stack: %8.8lux-%8.8lux\n",
			(ulong)(m+1), (ulong)m+BY2PG-4);
	dumplongs("stack", (ulong *)(ureg->sp - 32), 64);
	_dumpstack(ureg);
	dumparound(ureg->pc);
}
