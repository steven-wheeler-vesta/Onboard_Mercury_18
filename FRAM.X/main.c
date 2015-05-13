/* FRAM test
 *
 * Author: wheels
 *
 * Write an incrementing pattern of bytes to the first FRAM locations, read them
 * back and print them. Increment the start value for the pattern, and repeat.
 */

/* Set the configuration bits:
 * - No extended instruction set
 * - Oscillator = HS
 * - PLL = 4x
 * - SOSC set to digital => PORTC.1 and PORTC.0 are I/O
 */
#pragma config XINST = 0
#pragma config FOSC = HS2
#pragma config PLLCFG = 1
#pragma config SOSCSEL = 2

/* Use PIC18 Peripheral Libraries */
#define _PLIB 1


#include <xc.h>
#include <stdio.h>
#include "fram.h"
#include "mercury18.h"


/* A place to hold the values. The size of the array is arbitrary.
 */
unsigned char values[10];


/* Here is the code for the application itself.
 */
void main( void )
{
	int reg;
	unsigned char value, x;

	Open2USART(USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH, BAUD_38400);
	/* Initialize serial communications */
	TRISC = 0x00;
	TRISD = 0x20;

	init_SSP2();						/* Initialize the synchronous serial port */

	/* The test involves modifying the first 10 bytes of the FRAM and reading them back
	 * to verify the write. Because we don't want to write the same data all the time,
	 * we'll use the variable 'x' to contain a value that will be added to the register
	 * address to produce the data value that is to be written to a register during
	 * each write cycle.
	 */
	x = 0;
	for (;;)
	{
		printf("%02x\t", read_FRAM_status());

		/* The general format of a read is:
		 * 1) start the READ transaction at a particular register address,
		 * 2) read one or more consecutive registers, and
		 * 3) close the transaction.
		 *
		 * We could have read each register in a separate transaction, but
		 * we do them in a single transaction to show that it can be done.
		 */
		start_FRAM_read(0x1234);
		for (reg = 0; reg < 10; reg++)
		{
			values[reg] = read_FRAM_byte();
		}
		EE_SELECT = EE_IDLE;

		/* Now that the registers have been read, print their values.
		 */
		for (reg = 0; reg < 10; reg++)
		{
			printf("%02x  ", values[reg]);
		}
		printf("\r\n");

		/* Now write new values into the registers. As with the read transaction,
		 * we do the writes in a single transaction rather than separate writes
		 * for each read. Note that the call to enable writes must be performed
		 * prior to each write transaction.
		 */
		send_FRAM_command(EE_WREN);
		start_FRAM_write(0x1234);
		for (reg = 0; reg < 10; reg++)
		{
			write_FRAM_byte(reg + x);
		}
		EE_SELECT = EE_IDLE;

		/* Bump the base value prior to the next set of writes.
		 */
		x++;
	}
}