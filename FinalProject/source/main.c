/*	Author: sbala025
 *      Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Final Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
/*------Timer Functions------------------------------------------------------------------------------------------------------------------------*/
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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

void adc_init(){
	ADMUX = (1<<REFS0);	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/

/*------Joystick Functions---------------------------------------------------------------------------------------------------------------------*/
unsigned char JoystickPos(unsigned char x, unsigned char y){
	/*
 *	 x   |   y   |   return
 *    ----------------------------
 *	 1   |   1   |     1
 *	 2   |   1   |     2
 *	 3   |   1   |     3
 *	 1   |   2   |     4
 *	 2   |   2   |     5
 *	 3   |   2   |     6
 *	 1   |   3   |     7
 *	 2   |   3   |     8
 *	 3   |   3   |     9
 * 	*/
	if ((x == 1) && (y == 1)){
		return 1;
        }
        else if ((x == 2) && (y == 1)){
        	return 2;
    	}
    	else if ((x == 3) && (y == 1)){
        	return 3;
    	}
    	else if ((x == 1) && (y == 2)){
        	return 4;
    	}
    	else if ((x == 2) && (y == 2)){
        	return 0;
    	}
    	else if ((x == 3) && (y == 2)){
        	return 5;
    	}
    	else if ((x == 1) && (y == 3)){
        	return 6;
   	}
    	else if ((x == 2) && (y == 3)){
        	return 7;
    	}
    	else if ((x == 3) && (y == 3)){
        	return 8;
    	}
	else{
		return 0;
	}
}



int main(void) {
    	/* Insert DDR and PORT initializations */
	DDRA = 0x00; DDRA = 0xFF;
	DDRB = 0xFF; DDRB = 0x00;
    	/* Insert your solution below */
	 
   	while (1) {

    	}
    	return 1;
}
