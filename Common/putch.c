/* putch.c
 *
 * This is used to customize printf(). On Mercury18, we will normally want
 * to print to the second USART, which is the one that goes to the USB
 * interface.
 *
 * We would normally want to use the Write2USART call that's available in
 * plib, but that gives a linker error saying that the definition of
 * Write2USART in the library sources is inconsistent, which seems to mean
 * that it's defined differently than what's in the "u2write.c" file. That
 * makes no sense, though. Since we're not going to do 9-bit serial I/O,
 * we only have to copy the one line from the routine to get things working.
 */

#include <xc.h>
#include <p18cxxx.h>
#include <usart.h>

void putch( char data)
{
	while (Busy2USART())
		continue;
//	Write2USART(data);	// Should use this, but gives linker error
	TXREG2 = data;		// Write the data byte to the USART2
}

