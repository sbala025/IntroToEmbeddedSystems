/*	Author: sbala025
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	     
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
*/

/*-----INCLUDE STATEMENTS---------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#include <keypad.h>
#include <stdio.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LCDdisplay{text};

unsigned char output = 0x00;
unsigned char i = 0;

const unsigned char MAINTEXT[42] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','I','S',' ','L','E','G','E','N','D','.','.','.','W','A','I','T',' ','F','O','R',' ','I','T',' ','D','A','R','Y','!',' ',' ' ,' ',};

int D_Tick(int state){
	switch(state){
		case text:
			state = text; break;
		default:
			state = text; break;
	}
	switch(state){
		case text:
			for(int i = 0; i <= 16; i++){
				LCD_Cursor(i);
				LCD_WriteData(MAINTEXT[i+output-1]);
				//output++;
				if(output+i == 56){
					output = 0;
				}
				output++;
			}break;
		default: break;
	}
	return state;
}

int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0XF0; PORTA = 0X0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0XFF; PORTD = 0X00;
	/* Insert your solution below */
	static task task1;
    	task *tasks[] = { &task1 };
    	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

	const char start = 0;
	task1.state = start;
    	task1.period = 2;
    	task1.elapsedTime = task1.period;
    	task1.TickFct = &D_Tick;

	TimerSet(1);
    	TimerOn();
	
	LCD_init();

	while(1){
		for(unsigned char i = 0; i < numTasks; ++i) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}
