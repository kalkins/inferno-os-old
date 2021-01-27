#include "u.h"
#include "../port/lib.h"
#include "dat.h"
#include "mem.h"
#include "fns.h"

void
microdelay(int microsecond)
{
	int i;

	// The speed of QEMU is undefined, so we guess
	// that it's not faster than 500 MHz.
	microsecond *= 500;
	for(i=0; i<microsecond; i++)
		;
}

void delay(int millisecond)
{
	microdelay(1000*millisecond);
}
