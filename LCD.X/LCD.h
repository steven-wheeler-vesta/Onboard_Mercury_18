/* LCD.h
 * Author: wheels
 *
 * Useful definitions and function prototypes for the LCD interface.
 */

#ifndef __LCD_H
#define	__LCD_H

/* Define the bit assignments for connecting the LCD. We'll make this selectable.
 * Not that bit 0 of port F (on J6) is unavailable for I/O on the PIC18F66K90
 * processor, so we must make our assignments accordingly. We'll use bits 1-3
 * for the control signals, and bits 4-7 for the data. This gives us the
 * following connections:
 *
 * Mercury port pin     LCD connector pin
 *    1 (+5)                     2
 *    2 (GND)                    1
 *    3 (Enable)                 6
 *    4 (RS)                     4
 *    5 (RW)                     5
 *    6 (Unconnected)
 *    7 (D4)                    11
 *    8 (D5)                    12
 *    9 (D6)                    13
 *   10 (D7)                    14
 *
 * LCD connector pin 3 (Contrast) should be connected to a potentiometer that
 * can be adjusted between ground and +5, but tying it to one or the other
 * may be sufficient.
 */
 
#define LCD_Enable (3)
#define LCD_RS (1)
#define LCD_RW (2)
#define LCD_RDY (7)

/* Only ONE of the following conditional sections should be enabled.
 */

#if 0
  #define LCDPORT PORTD
  #define LCDTRIS TRISD
#endif

#if 1
  #define LCDPORT PORTE
  #define LCDTRIS TRISE
#endif

#if 0
  #define LCDPORT PORTF
  #define LCDTRIS TRISF
#endif


void lcd_command( unsigned char cmd );
void lcd_data( unsigned char info );
unsigned char lcd_read( unsigned char cmd );
void lcd_init( void );

#endif	/* __LCD_H */

