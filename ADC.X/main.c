/* Analog-to-Digital demo app.
 *
 * This application performs continuous conversions and displays of some of the
 * analog channels.
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
#include <adc.h>
#include <usart.h>
#include "mercury18.h"


/* For a simple demo, we won't worry about all of the channels. For simplicity,
 * we'll monitor the first four channels, so we have results in simple columns.
 */
unsigned char channels[4] = {ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3};


/* Main routine for the application.
 */
void main()
{
	int chan, result;

	Open2USART(USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH, BAUD_38400);
	OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_8_TAD,
			ADC_CH0 & ADC_CH1 & ADC_CH2 & ADC_CH3 & ADC_INT_OFF,
			ADC_REF_VDD_VDD & ADC_REF_VDD_VSS);
	chan = 0;
	while (1)
	{
		SelChanConvADC(channels[chan]);
//		while (BusyADC())
			;
		result = ReadADC();
		printf("%i\t", result);
		chan = (chan + 1) & 3;
		if (chan == 0) printf("\r\n");
	}
}