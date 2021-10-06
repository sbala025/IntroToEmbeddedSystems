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

//ENUM INITIALIZATION
enum States {Start, OFF_R, OFF_P, ON_R, ON_P} state;

//TICK FUNCTION
void Tick(){
	unsigned char input = PINA & 0x01;
	switch(state){
		case Start:
			state = OFF_R;
			break;
		 case OFF_R:
                        if(input == 1){
                                state = ON_P;
                                PORTB = 0x02;
                        }
                        else{   
                                state = OFF_R;
                                PORTB = 0x01;
                        }
                        break;
		case ON_P:
			if(input == 1){
				state = ON_P;
				PORTB = 0x02;
			}
			else{
				state = ON_R;
				PORTB = 0x02;
			}
			break;
		case ON_R:
                        if(input == 1){
                                state = OFF_P;
                                PORTB = 0x01;
                        }
                        else{
                                state = ON_R;
                                PORTB = 0x02;
                        }
                        break;
		case OFF_P:
                        if(input == 1){
                                state = OFF_P;
                                PORTB = 0x01;
                        }
                        else{
                                state = OFF_R;
                                PORTB = 0x01;
                        }
                        break;
		default:
			case = OFF_R;
			break;
	}
}

//MAIN FUNCTION
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
