/* LCD example program
 * Author: wheels
 *
 * This example interfaces with an LCD connected to one of the extra I/O ports
 * (J4, J5, or J6) on the Mercury18. It presumes an alphanumeric LCD controlled
 * by a Hitachi 44780 or equivalent. The interface will use 4-bit mode, so the
 * control and data lines can be on the same port. We will use our own LCD
 * interface routines for two reasons:
 *   1. For compatibility (more or less) with the routines on Mercury16, and
 *   2. The PLIB routines presume the use of Port E, which may not be what you
 *      want to use in your application.
 *
 * Note that bit 0 of port F (J6) is not available for I/O on the PIC18F66K90,
 * so we must make our pin assignments such that it does not matter.
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


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "mercury18.h"
#include "lcd.h"


/* Define the only variable here, so that the debugger can see it.
 */
unsigned char foo;

/* This is the main routine in the application. It initializes the LCD, then
 * continually writes characters to the display.
 */
int main( void )
{
	lcd_init();
	foo = ' ';
	for (;;)
	{
		lcd_data(foo++);
		if (foo == 'Z' + 1) foo = 'a';
		if (foo > 'z') foo = ' ';
	}
    return (EXIT_SUCCESS);
}

