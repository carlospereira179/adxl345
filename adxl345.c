/**
 * 	ADXL 345 Library v1.0
 * 	Library for using the ADXL345, with SPI interface with the MSP430G2553 that comes with the MSP430 Launchpad.
 *
 * 	The SPI interface uses:
 *
 * 	MSP430G2553|		|ADXL345
 * 	 P1.1(MISO)|--------|SDO
 * 	 P1.2(MOSI)|--------|SDA
 * 	  P1.4(SCK)|--------|SCL
 * 	   P1.5(CS)|--------|CS
 *
 * 	adxl345.c
 * 	adxl345.h
 *
 * 	Created by: Carlos Pereira, Ícaro Nascimento and Rodrigo Sapucaia
 * 	Released into the public domain.
 */
#include <msp430.h>

#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37


void start_adxl345(void)						//Configure the MSP430 to use SPI interface
{
	P1DIR |= BIT5;								//P1.5 as Chip Select
	P1OUT |= BIT5;								//Set  Chip Select as high
	P1SEL = BIT1 | BIT2 | BIT4;					//P1.1 as MISO, P1.2 as MOSI and P1.4 as SCK
	P1SEL2 = BIT1 | BIT2 | BIT4;				//P1.1 as MISO, P1.2 as MOSI and P1.4 as SCK

	UCA0CTL1 = UCSWRST;							// Reset mode to the setup
	UCA0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC;// 3-pin, 8-bit SPI master, MSB first
	UCA0CTL1 |= UCSSEL_2;						// SMCLK
	UCA0MCTL = 0;								// No modulation
	IE2 |= BIT0 + BIT1;
	UCA0CTL1 &= ~UCSWRST;						// Leave the reset mode
}

int read_x(void)					// Return a 16 bit X-Axis information
{
	int msByte,msByte16,lsByte,measure;

	lsByte = read_spi(DATAX0);		// Read data via SPI

	msByte = read_spi(DATAX1);		// Read data via SPI

	msByte16 = (msByte << 8);		// Shifts the most significant Byte in 1 byte
	measure = msByte16 | lsByte;	// Turn the msByte and the lsByte in one 2 bytes information

	return measure;
}
int read_y(void)					// Return a 16 bit Y-Axis information
{
	int msByte,msByte16,lsByte,measure;
	
	lsByte = read_spi(DATAY0);		// Read data via SPI

	msByte = read_spi(DATAY1);		// Read data via SPI

	msByte16 = (msByte << 8);		// Shifts the most significant Byte in 1 byte
	measure = msByte16 | lsByte;	// Turn the msByte and the lsByte in one 2 bytes information

	return measure;
}

int read_z(void)					// Return a 16 bit Z-Axis information
{
	int msByte, msByte16, lsByte, measure;

	lsByte = read_spi(DATAZ0);		// Read data via SPI

	msByte = read_spi(DATAZ1);		// Read data via SPI

	msByte16 = (msByte << 8);		// Shifts the most significant Byte in 1 byte
	measure = msByte16 | lsByte;	// Turn the msByte and the lsByte in one 2 bytes information

	return measure;
}

int read_spi(int addr)
{
	int info;

	P1OUT &= (~BIT5);				// Select Device
	while (!(IFG2 & UCA0TXIFG));	// Wait until TX buffer get ready
	UCA0TXBUF = addr;				// Send data address over SPI to Slave
	while (!(IFG2 & UCA0RXIFG));	// Wait all data get to the buffer
	info = UCA0RXBUF;				// Store received data
	P1OUT |= (BIT5);				// Unselect Device

	return info;
}
void write_spi(int addr, int info)
{
	P1OUT &= (~BIT5);				// Select Device
	while (!(IFG2 & UCA0TXIFG));	// Wait until TX buffer get ready
	UCA0TXBUF = addr;				// Send data address over SPI to Slave
	while (!(IFG2 & UCA0TXIFG));	// Wait until TX buffer get ready
	UCA0TXBUF = info;				// Send data address over SPI to Slave
	P1OUT |= (BIT5);				// Unselect Device
}
