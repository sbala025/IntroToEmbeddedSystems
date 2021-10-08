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
enum States {Start, Controller, X, Y, P, X_pressed, Y_pressed, P_pressed, checkCode} state;

void Tick(){
	char fillIn[4];
	int count = 0;
	char unlock[4];
		unlock[0] = '#';
   		unlock[1] = 'X';
   		unlock[2] = 'Y';
		unlock[3] = 'X';
	char checkArr = 1;
	char input = PINA;
	char output = 0x00;
	//input
	switch(state){
		case Start:
			state = Controller;
			break;
		case Controller:
			if(count == 4){state = checkCode;}
			else if(input == 0x01){state = X;}
			else if(input == 0x02){state = Y;}
			else if(input == 0x04){state = P;}
			else{state = Controller;}
			break;
		case X:
			if (input == 0x01){state = X_pressed;}
			else{state = Controller;}
			break;
		case Y:
			if (input == 0x02){state = Y_pressed;}
			else{state = Controller;}
                        break;
		case P:
			if (input == 0x04){state = P_pressed;}
                        else{state = Controller;}
                        break;
		case X_pressed:
			if (input == 0x01){state = X_pressed;}
                        else{state = Controller;}
                        break;
		case Y_pressed:
			if (input == 0x02){state = Y_pressed;}
                        else{state = Controller;}
                        break;
		case P_pressed:
			if (input == 0x04){state = P_pressed;}
                        else{state = Controller;}
                        break;
		case checkCode:
			state = Controller;
			break;
		default:
			state = Controller;
                        break;
	}
	switch(state){
		case Start:
			output = 0x00;
			break;
		case Controller:
			break;
		case X:
			fillIn[count] = 'X';
			count = count + 1;
			break;
		case Y:
                        fillIn[count] = 'Y';
			count = count + 1;
                        break;
		case P:
                        fillIn[count] = 'P';
                        count = count + 1;
			break;
		case X_pressed:
			break;
		case Y_pressed:
			break;
		case P_pressed:
			break;
		case checkCode:
			count = 0;
			for(int i = 0; i < 4; i++){
				if(fillIn[i] != unlock[i]){checkArr = 0;}
			}
			if(checkArr == true){ output = 0x01;}
			else{ output = 0x00;}
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
