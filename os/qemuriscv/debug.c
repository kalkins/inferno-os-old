#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "debug.h"
#include "uart.h"

int debug = 0;

void
setdebug(int n)
{
	debug = n;
}

int
getdebug(void)
{
	return debug;
}

void printnum(ulong num)
{
	if (num > 9) {
		printnum(num/10);
		num = num % 10;
	}

	switch(num) {
	case 0:
		uartputc('0');
		break;
	case 1:
		uartputc('1');
		break;
	case 2:
		uartputc('2');
		break;
	case 3:
		uartputc('3');
		break;
	case 4:
		uartputc('4');
		break;
	case 5:
		uartputc('5');
		break;
	case 6:
		uartputc('6');
		break;
	case 7:
		uartputc('7');
		break;
	case 8:
		uartputc('8');
		break;
	case 9:
		uartputc('9');
		break;
	default:
		uartputc('?');
		uartputc(num);
		uartputc('?');
		break;
	}
}

void
debugprint(char *s)
{
	int len;

	if (debug == 0)
		return;

	len = strlen(s);
	uartputs("DEBUG ", 6);
	uartputs(s, len);
	uartputc('\n');
}

void
debugprintarg(char *name, long val)
{
	int len;

	if (debug == 0)
		return;

	len = strlen(name);
	uartputs("DEBUG ", 6);
	uartputs(name, len);
	uartputs(" = ", 3);
	if (val < 0) {
		uartputc('-');
		val -= val;
	}
	printnum(val);
	uartputc('\n');
}

void
debugprintuarg(char *name, ulong val)
{
	int len;

	if (debug == 0)
		return;

	len = strlen(name);
	uartputs("DEBUG ", 6);
	uartputs(name, len);
	uartputs(" = ", 3);
	printnum(val);
	uartputc('\n');
}

// This function is called from the assembly function breakpoint(),
// with the callers address
void
_breakpoint(ulong addr)
{
	print("BREAKPOINT on address 0x%lux. Press any key to continue\n", addr);
	uartgetc();
}
