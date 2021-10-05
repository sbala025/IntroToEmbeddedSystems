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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	/* Initialize all variables */
	unsigned char main_input = 0x00;
	unsigned char half1 = 0x00;
	unsigned char half2 = 0x00;
	//unsigned char output = 0x00;
	/* Insert your solution below */
	while (1) {
		main_input = PINA;
		half1 = main_input << 4;
		half2 = main_input >> 4;
		PORTB = half2;
		PORTC = half1; 
	}
	return 1;
}
