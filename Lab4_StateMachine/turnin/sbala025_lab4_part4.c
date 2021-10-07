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
enum States {Start, Controller, Pound, Pound_down, Y_unlocked, Y_maybe, Y_down, Inside, Inside_down}state;

void Tick(){
	unsigned char input = PINA & 0x87;
	unsigned char output = PORTB;
	//input
	switch(state){
		case Start:
			state = Controller; break;
		case Controller:
			if(input == 0x04){state = Pound;}
			else if(input == 0x80){state = Inside;}
			else{state = Controller;} 
			break;
		case Inside:
			if(input == 0x80){state = Inside;}
			else{state = Controller;} 
                        break;
		//case Inside_down:
		//	if(input == 0x80){state = Inside_down;}
		//	else{state = Controller;}
                //        break;
		case Pound:
			if(input == 0x04){state = Pound;}
			else if(input == 0x00){state = Y_maybe;}
			else{state = Controller;}
			break;
		//case Pound_down:
		//	if(input == 0x04){state = Pound_down;}
		//	else{state = Y_maybe;}
		//	break;
		case Y_maybe:
			if(input == 0x02 && (PORTB == 0x00)){state = Y_unlocked;}
			else if(input == 0x00){state = Y_maybe;}
			else{state = Controller;}
			break;
		//case Y_down:
		//	if(input == 0x02){state = Y_down;}
		//	else{state = Controller;}
		//	break;
		case Y_unlocked:
                        if(input == 0x02){state = Y_unlocked;}
                        else{state = Controller;}
                        break;
		default:
			state = Controller;
			break;
	}
	//output
	switch(state){
		case Start:
			output = 0x00;
			break;
		case Controller:
			break;
		case Inside:
			output = 0x00;
                        break;
		case Inside_down:
			break;
		case Pound:
			break;
		case Pound_down:
			break;
		case Y_maybe:
			break;
 		case Y_down:
			break;
		case Y_unlocked:
			output = 0x01;
			break;
	}
	PORTB = output;
}

int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	/* Insert your solution below */
	while (1) {
		Tick();
	}
	return 1;
}
