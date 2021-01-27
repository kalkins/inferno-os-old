#include "u.h"
#include "../port/lib.h"
#include "dat.h"
#include "fns.h"
#include "uart.h"
#include "debug.h"

#define UART_BASE 0x10000000
#define FIFO_SIZE 16
#define RBR 0 // input
#define THR 0 // output
#define DLL 0 // divisor LSB
#define DLM 1 // divisor MSB
#define IER 1 // interrupt enable
#define FCR 2 // FIFO control
#define ISR 2 // interrupt status
#define LCR 3 // line control
#define LSR 5 // line status

#define Reg(reg) ((volatile unsigned char *)(UART_BASE + reg))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

void
uartsetup(void)
{
	// Disable interrupts
	WriteReg(IER, 0x00);

	// Set baud rate to 9600. This requires DLAB 1
	WriteReg(LCR, 1<<7);
	WriteReg(DLL, 0x0C);
	WriteReg(DLM, 0x00);

	/*
	 * Set up LCR:
	 * Bit 0-1 = 0b11    Use 8-bit words
	 * Bit 2   = 0b0     One stop bit
	 * Bit 3-5 = 0b000   No parity
	 * Bit 6   = 0b0     Break signal disable
	 * Bit 7   = 0b0     DLAB 0, communication regs available
	 *
	 * 0b00000011 = 0x03 = 3
	 */
	WriteReg(LCR, 0x03);

	// Enable and clear FIFO
	WriteReg(FCR, 0x7);

	// Enable interrupts
	WriteReg(IER, 0x01);
}

void
uartputc(int c)
{
	// Wait until the FIFO is empty.
	// This is marked by a 1 in bit 5 of LSR.
	while ((ReadReg(LSR) & 1<<5) == 0) {}

	// Write the byte to THR
	WriteReg(THR, c);
}

void
uartputs(char *s, int len)
{
	int i = 0; // The index in the string
	int f; // The number of bytes written to the FIFO

	while (i < len) {
		// Wait until the FIFO is empty.
		while ((ReadReg(LSR) & 1<<5) == 0) {}

		// Write up to 16 bytes to the FIFO
		for (f = 0; f < FIFO_SIZE && i < len; f++) {
			WriteReg(THR, s[i]);
			i++;
		}
	}
}

int
uartgetc(void)
{
	// Wait until there is data in the FIFO.
	// This is marked by a 1 in bit 0 of LSR.
	while ((ReadReg(LSR) & 1) == 0) {}

	// Read the byte from RBR.
	return ReadReg(RBR);
}

void
uartintr(void)
{
	char c;

	// Read incoming characters
	while ((ReadReg(LSR) & 1) == 1) {
		c = ReadReg(RBR);
		DBG_IF {
			print("UART Incoming: %c\n", c);
		} else {
			print("%c", c);
		}
	}
}
