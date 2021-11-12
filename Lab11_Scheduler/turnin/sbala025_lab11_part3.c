/*	Author: sbala025
 *      Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #1
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

/*--------FIND GCD FUNCTION-------------------------------------*/
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;
}

/*--------TASK SCHEDULER----------------------------------------*/
typedef struct task {
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} task;

/*--------FSM---------------------------------------------------*/
enum Keypad{ key}k_state;
unsigned char x;

int Keypad_Tick(int state){
	//unsigned char x;	
	x = GetKeypadKey();
	switch(k_state){
	//	case Start:k_state = key; break;
		case key:
			switch(x) {
				case '\0': 	keypad = 0x1F; break;
				case '1':	keypad = 0x01; break;
				case '2':	keypad = 0x02; break;
				case '3':	keypad = 0x03; break;
				case '4':	keypad = 0x04; break;
				case '5':	keypad = 0x05; break;
				case '6':	keypad = 0x06; break;
				case '7':	keypad = 0x07; break;
				case '8':	keypad = 0x08; break;
				case '9':	keypad = 0x09; break;
				case 'A':	keypad = 0x0A; break;
				case 'B':	keypad = 0x0B; break;
				case 'C':	keypad = 0x0C; break;
				case 'D':	keypad = 0x0D; break;
				case '*':	keypad = 0x0E; break;
				case '0':	keypad = 0x00; break;
				case '#':	keypad = 0x0F; break;
				default:	keypad = 0x1B; break;
			}
			LCD_ClearScreen();
                        LCD_Cursor(1);
                        LCD_WriteData(keypad + '0');
			//PORTB = keypad; break;
		default: k_state = key; break;
	} return state;
}

/*--------MAIN--------------------------------------------------*/
int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0XFF; PORTA = 0X00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0XFF; PORTD = 0X00;
	/* Insert your solution below */
	static task task1;
    	task *tasks[] = { &task1 };
    	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    	const char start = 0;
    	task1.state = start;
    	task1.period = 50;
    	task1.elapsedTime = task1.period;
    	task1.TickFct = &KeypadTick;

    	TimerSet(50);
    	TimerOn();
	LCD_init();
	LCD_ClearScreen();

    	//unsigned short i;
    	while (1) {
		for (unsigned char i = 0; i < numTasks; ++i) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 50;
		}
		while(!TimerFlag);
		TimerFlag = 0;
    	}
    	return 1;
}
