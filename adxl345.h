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
#ifndef ADXL3453_H_
#define ADXL3453_H_

void start_adxl345(void);

int read_x(void);

int read_y(void);

int read_z(void);

void read_spi(int addr);

void write_spi(int addr);

#endif /* ADXL3453_H_ */
