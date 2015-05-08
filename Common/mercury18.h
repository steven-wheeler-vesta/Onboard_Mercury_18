/* mercury18.h
 *
 * This file contains common equates for use with Mercury.
 */

#ifndef MERCURY18_H
#define MERCURY18_H

/* Start with the hardware-related values that are immutable.
 */
#define Fosc 64000000L


/* Designate the bits associated with the onboard LED */
#define LEDbit PORTCbits.RC3
#define LEDTRIS TRISCbits.TRISC3



/* There are three different equations that are used to calculate the baud
 * rate divisor. They are all similar, only varying in the constant used as a
 * scaler. For the hardware configuration that uses an 8-bit divisor with
 * BRGH = 0, the scaler is 64. For an 8-bit divisor with BRGH = 1, the scaler
 * is 16. The configuration for a 16-bit divisor with BRGH = 0 also uses a
 * scaler of 16. For a 16-bit divisor with BRGH = 1, the scaler is 4. The
 * general equation is:
 *
 * divisor = Fosc/(scaler * baud) - 1
 *
 * This gives us the following values (for Fosc = 64MHz):
 *
 *  Baud     BRGH=0    BRGH=1    BRGH=0    BRGH=1
 *          BRG16=0   BRG16=0   BRG16=1   BRG16=1
 * ==============================================
 * 115200       ---        34        34       138
 *  38400        25       103       103       416
 *  31250        31       127       127       511
 *  19200        51       207       207       832
 *   9600       103       ---       416      1666
 *   4800       207       ---       832      3332
 *   2400       ---       ---      1666      6666
 *   1200       ---       ---      3332     13332
 *    600       ---       ---      6666     26666
 *    300       ---       ---     13332     53332
 *    150       ---       ---     26666       ---
 *    134.5     ---       ---     29739       ---
 *    110       ---       ---     36383       ---
 *
 * Entries without numbers are either too large to fit into the register, or
 * produce a baud rate that is too far out of tolerance (about 2%) to work
 * properly.
 *
 * If you want more options for baud rates slower than in the above table
 * (for example, when working with old hardware), you can compile without
 * using the PLL, which will drop Fosc down to 8MHz
 *
 * The following constants are defined presuming that BRGH=1 and BRG16=0, and
 * that the PLL is active.
 */

#define BAUD_115200 34
#define BAUD_38400 103
#define BAUD_19200 207


#endif	// MERCURY18_H
