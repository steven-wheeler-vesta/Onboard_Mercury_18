/* Simple blink demo.
 *
 * Author: wheels
 */

#include "xc.h"
#include "mercury18.h"


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



/* This will blink the onboard LED. It will also generate a series of square
 * waves on port E (J5). Each bit will toggle at 1/2 the frequency of the
 * preceding bit.
 */
main(void)
{
	unsigned int i;
	unsigned char j;

	LEDTRIS = 0;			/* Set LED bit as output */
	TRISE = 0;			/* All port E bits outputs */
	j = 0;
	for (;;)
	{
		LEDbit = j >> 5;	/* Slow LED blink rate down */
		PORTE = j++;
		for (i = 10000; i--;)
			continue;
	}
}