/* ADC.C
 * Simple interface to A/D on PIC18F66K90.
 * Not generic; specific to sample app.
 */

#include <xc.h>
#include "adc.h"


/* Initialize the module (or, at least the part we'll be using).
 */
void init_adc()
{
	TRISA = 7;		// Set A.0-2 as input
	ANSEL0 = 7;		// A.0-2 configured as analog
	ADCON1 = 0xC0;	// Right-justified, Fosc/4, Vdd+, Vss-
//	ADFM = 1;		// Right-justified result
}


/* Produce a conversion result on the specified channel.
 */
int convert(int channel)
{
	int result;

	// Set channel and turn A/D module on
	ADCON0 = ((channel & 0x1F) << 2) | 1;
	PORTDbits.RD7 = 1;	/* Debug for timing */
	for (result = 0; result < 500; result++)
		;
	PORTDbits.RD7 = 0;	/* Debug for timing */
	GO = 1;			// Start conversion
	while (GO_NOT_DONE)
		continue;	// Wait for done
	result = ADRES;
	return result;
}

