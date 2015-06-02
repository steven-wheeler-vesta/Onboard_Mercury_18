/* PWM example.
 *
 * Generates PWM outputs on CCP6, CCP7, CCP8, and CCP9, which can be found on
 * J5.9, J5.8, J5.7, and J5.6, respectively.
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


#include <pic18.h>
#include <stdio.h>
#include <pwm.h>
#include "mercury18.h"


void main()
{
	unsigned char period;
	unsigned int duty_cycle, delay;

	/* Open the serial channel so we can see the period information. */
	Open2USART(USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH, BAUD_38400);

	for (;;)
	{
		/* The period is an 8-bit quantity, but it can't be too short
		 * if we want to have different duty cycles available.
		 */
		for (period = 10; period < 255; period++)
		{
			printf("%i\t", period);
			/* Configure the CCP channels for the desired period */
			OpenPWM6(period, CCP_6_SEL_TMR12);
			OpenPWM7(period, CCP_7_SEL_TMR12);
			OpenPWM8(period, CCP_8_SEL_TMR74);
			OpenPWM9(period, CCP_9_SEL_TMR74);
			for (duty_cycle = 1; duty_cycle < 1024; duty_cycle++)
			{
				/* Set the duty cycle for each output */
				SetDCPWM6(duty_cycle);
				SetDCPWM7(1024 - duty_cycle);
				SetDCPWM8(duty_cycle);
				SetDCPWM9(1024 - duty_cycle);
				/* Slow things down a bit */
				for (delay = 0; delay < 1000; delay++)
					;
			}
		}
	}
}