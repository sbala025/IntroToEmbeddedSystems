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

enum States {Start, OFF, LED, PAUSE, RIGHT, LEFT} state;
volatile unsigned char TimerFlag = 0;
/* Internal variables for mapping AVR’s ISR to our cleaner Timer ISR model */
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char switchDirection = 0x00;

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

void Tick() {
	unsigned char input = ~PINA & 0X01;
	unsigned char output = PORTB;
	switch(state) {
		case Start:	
			state = OFF; 
			break;
		case OFF:	
			state = LED; 
			break;
		case LED:	
			if (input == 0x01) {
				state = PAUSE;
			}else {
				state = LED;
			}break;
		case PAUSE:	
			if (input == 0x01) {
				state = PAUSE;
			}else {
				state = LED;
			}break;
		/*case LEFT:	
			if (input == 0x01) {
				state = RIGHT;
			}else {
				state = LEFT;
			}break;
		case RIGHT:	
			if (input == 0x01) {
				state = RIGHT;
			}else {
				state = OFF;
			}break;*/
		default:	
			state = Start; 
			break;
	}
	switch (state) {
		case Start:     
			break;
               	case OFF:      
			output = 0x00; 
			break;
		case LED:
			if (switchDirection == 0x00 && (output == 0x04)) {
				output = output >> 1
				switchDirection = 0x01;
			}else if(switchDirection == 0x00 && (output != 0x04)) {
				output = output << 1;
			}else if(switchDirection == 0x01 && (output == 0x01)){
				output = output << 1;
                                switchDirection = 0x00;
			}else if(switchDirection == 0x01 && (output != 0x01)){
                        	output = output >> 1;
			}
			break;
		case PAUSE: 	
			break;
		/*case LEFT:	
			break;
		case RIGHT: 	
			break;*/
                default:        
			break;
	}
	PORTB = output;
}

void main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(300);
    TimerOn();
    while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
}

