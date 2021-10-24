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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Actual_start, initialize, plus, plus_down, minus_down, minus, reset} state;
volatile unsigned char TimerFlag = 0;
/* Internal variables for mapping AVR’s ISR to our cleaner Timer ISR model */
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char count = 0;
void TimerOn() {
TCCR1B = 0x0B;
OCR1A = 125;
TIMSK1 = 0x02;
TCNT1 = 0;
_avr_timer_cntcurr = _avr_timer_M;
SREG |= 0x80;
}

void TimerOff() {
TCCR1B = 0x00;
}

void TimerISR() { 
TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
_avr_timer_cntcurr--;
if (_avr_timer_cntcurr == 0) {
	TimerISR();
	_avr_timer_cntcurr = _avr_timer_M;
}
}

void TimerSet (unsigned long M) {
_avr_timer_M = M;
_avr_timer_cntcurr = _avr_timer_M;
}

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
			state = plus_down;
			break;
		case plus_down:
			if(count == 10){state = plus;}
			else if(input == 0x01){state = plus_down;}
			else if(input == 0x02){state = minus;}
			else if (input == 0x03){state = reset;}
			else {state = initialize;}
                        		break;
		case minus_down:
				if(count == 10){state = minus;}
                        	else if(input == 0x02){state = minus_down;}
                        	else if(input == 0x01){state = plus;}
                        	else if (input == 0x03){state = reset;}
                        	else {state = initialize;}
                        	break;
		case minus:
			state = minus_down;
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
		case minus_down:
		case plus_down:
			break;
		case initialize:
			break;
		case reset:
			output = 0;
                        break;
		case plus:
			if(output < 9){output = output + 1;}
			count = 0;
			break;
		case minus:
			if(output > 0){output = output - 1;}
			count = 0;
			break;
		default:
			output = 7;
                        break;
	}
	count++;
	PORTC = output;
}
/*MAIN FUNCTION*/
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	TimerSet(100);
    	TimerOn();
    	while (1) {
		Tick();
		while(!TimerFlag) {};
		TimerFlag = 0;
   	 }
}

