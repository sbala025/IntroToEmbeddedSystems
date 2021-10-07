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
//#include "RIMS.h"
#endif
//INITIALIZE ENUM
enum States {Start, Actual_start, initialize, plus, button_down, minus, reset} state;

//TICK FUNCTION
void Tick(){
	unsigned char input = PINA & 0x03;
	unsigned char output = PORTC;
	switch (state){
		case Start:
			state = Actual_start;
			break;
		case Actual_start: 
			state = initialize;
                        break;
		case initialize:
			if(input == 0x03){state = reset;}
			else if(input == 0x02){state = minus;}
			else if(input == 0x01){state = plus;}
			else{state = initialize;}
			break;
		case reset:
			if(input == 0x02){state = minus;}
                        else if(input == 0x01){state = plus;}
			else{state = reset;}
			break;
		case plus:
			state = button_down;
			break;
		case button_down:
			if(input == 0x01|| input == 0x02){state = button_down;}
			else {state = initialize;}
                        break;
		case minus:
			state = button_down;
			break;
		default:
			state = initialize;
                        break;
	}
	switch (state){	
		case Start:
		case Actual_start:
			output = 7;
                        break;
		case button_down:
			break;
		case initialize:
			break;
		case reset:
			output = 0;
                        break;
		case plus:
			if(output < 9){output = output + 1;}
			break;
		case minus:
			if(output > 0){output = output - 1;}
			break;
		default:
			output = 7;
                        break;
	}
	PORTC = output;
}
//MAIN FUNCTION
int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	/* Insert your solution below */
	while (1) {
		Tick();
	}
	return 1;
}
