/*	Author: sbala025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRC = 0XFF; PORTC = 0X00;

	/*Initialize variables*/
	unsigned char input = 0x00;
	unsigned char output = 0x00;

	/* Insert your solution below */
	while (1) {
		input = PINA;
		input = input & 0x0F;
		if(input == 0) {output = 0x40;}
		else if(input == 1 || input == 2) {output = 0x60;}
		else if(input == 4 || input == 3) {output = 0x70;}
		else if(input == 5 || input == 6) {output = 0x38;}
		else if(input == 7 || input == 8 || input == 9) {output = 0x3C;}
		else if(input == 10 || input == 11 || input == 12) {output = 0x3E;}
		else {output = 0x3F;}
		PORTC = output;	
	}
	return 1;
}
