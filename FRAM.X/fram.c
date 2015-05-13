/* eeprom.c
 *
 * This file contains the routines that provide access to the FM25W256 FRAM
 * (EEPROM equivalent device) on the Mercury board.
 */

#include <xc.h>
#include <spi.h>
#include "fram.h"


/* Initialize the SSP2 channel
 */
void init_SSP2( void )
{
	OpenSPI2(SPI_FOSC_64, MODE_00, SMPMID);	/* Initialize the synchronous serial port */
}


/* Send one byte via the SSP2 port.
 */
void write_FRAM_byte( unsigned char value )
{
	WriteSPI2(value);
}


/* Receive one byte via the SSP2 port.
 */
unsigned char read_FRAM_byte()
{
	unsigned char result;

//	PORTD &= 0xF7;
	result = ReadSPI2();				/* Get the return value */
	return result;
}


/* Open a write transaction at a specified register address.
 */
void start_FRAM_write( int address )
{
	EE_HOLD = 1;
	EE_WPROT = 1;
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(EE_WRITE);			/* Tell the chip we're writing to it */
	write_FRAM_byte(address >> 8);		/* Send high byte of address */
	write_FRAM_byte(address & 0xFF);	/* Send low byte of address */
}


/* Send a single-byte command to the FRAM.
 */
void send_FRAM_command( unsigned char command )
{
	EE_HOLD = 1;
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(command);
	EE_SELECT = EE_IDLE;
}


/* Open a read transaction at the specified register address.
 */
void start_FRAM_read( int address )
{
	EE_HOLD = 1;
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(EE_READ);			/* Tell the chip we're reading from it */
	write_FRAM_byte(address >> 8);		/* Send high byte of address */
	write_FRAM_byte(address & 0xFF);	/* Send low byte of address */
}


unsigned char read_FRAM_status( void )
{
	unsigned char temp;

	EE_HOLD = 1;
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(EE_RDSR);
//	write_FRAM_byte(0xFF);				/* Dummy for transfer */
	temp = read_FRAM_byte();
	EE_SELECT = EE_IDLE;
	return temp;
}