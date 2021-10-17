/*	Author: sbala025
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
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
enum States {Start, Down, Reset, Press1, Press5, Press2, Press6, Press3, Press7, Press4, Press8} state;

//TICK FUNCTION
void Tick(){
	unsigned char input = ~PINA;
	unsigned char output = PORTB;
	unsigned char count = 0;
	switch(state){
		case Start:
			state = Reset;
			break;
		case Reset:
			if(input == 0){state = Reset;}
			else if(count == 0){state = Press1;}
			else if(count == 1){state = Press2;}
			else if(count == 2){state = Press3;}
			else if(count == 3){state = Press4;}
			else if(count == 4){state = Press5;}
			else if(count == 5){state = Press6;}
			else if(count == 6){state = Press7;}
			else{state = Press8;}
		case Press1:
			state = Down;
			break;
		case Down:
			if(input != 0x00){state = Down;}
			else{state = Reset;}
		case Press2:
			state = Down;
                        break;
		case Press3:
			state = Down;
                        break;
		case Press4:
			state = Down;
                        break;
		case Press5:
			state = Down;
                        break;
		case Press6:
			state = Down;
                        break;
		case Press7:
			state = Down;
                        break;
		case Press8:
			state = Down;
                        break;
		default:
			state = Reset;
			break;

	}
	switch(state){
		case Start:
			break;
		case Reset:
			break;
		case Down:
			break;
		case Press1:
			count = 1;
			output = 0x21;
			break;
		case Press2:
			count = 2;
			output = 0x012;
			break;
		case Press3: 
			count = 3;
			output = 0x0C;
			break;
		case Press4:
			count = 4;
			output = 0x33;
			break;
		case Press5:
			count = 5;
			output = 0x38;
			break;
		case Press6:
			count = 7;
			output = 0x07;
			break;
		case Press7:
			count = 8;
			output = 0x3C;
			break;
		case Press8:
			count = 0;
			output = 0x3F;
			break;
		default:
			break;
	}
	PORTB = output;
}

//MAIN FUNCTION
int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char count = 0;
	/* Insert your solution below */
	while (1) {
		Tick();
	}
	return 1;
}
