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
	DDRB = 0X00; PORTB = 0XFF;
	DDRC = 0XFF; PORTC = 0X00;

	/*Initialize all variables*/
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;

	/* Insert your solution below */
	while (1) {
		tmpA = PINA;
		tmpB = PINB;
		tmpC = 0x00;
		while(tmpA != 0x00){
			if((tmpA & 0x80) == 0x80){tmpC = tmpC + 1;}
			tmpA = tmpA << 1;
		}
		while(tmpB != 0x00){
                        if((tmpB & 0x80) == 0x80){tmpC = tmpC + 1;}
                        tmpB = tmpB << 1;
                }
		PORTC = tmpC;
	}
	return 1;
}
