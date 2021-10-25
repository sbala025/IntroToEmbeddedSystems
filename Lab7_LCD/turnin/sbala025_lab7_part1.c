/*	Author: sbala025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *	https://drive.google.com/drive/folders/10inGIeWd93lPLnPaVi759IQ6cs0OtcFV?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Actual_start, initialize, plus, plus_down, minus_down, minus, reset} state;
volatile unsigned char TimerFlag = 0;
/* Internal variables for mapping AVR’s ISR to our cleaner Timer ISR model */
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char count = 0;
unsigned char output = 0;
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
	unsigned char input = ~PINA & 0x03;
	switch (state){
		case Start:
			state = Actual_start;
			break;
		case Actual_start: 
			state = initialize;
                        		break;
		case initialize:
			LCD_Cursor(1);
			LCD_WriteData(output + '0');
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
			count = 0;
			break;
		case plus_down:
			LCD_Cursor(1);
			LCD_WriteData(output + '0');
			count++;
			if(count == 9){state = plus; count = 0;}
			else if(input == 0x01){state = plus_down;}
			else if(input == 0x02){state = minus;}
			else if (input == 0x03){state = reset;}
			else {state = initialize;}
                        		break;
		case minus_down:
			LCD_Cursor(1);
			LCD_WriteData(output + '0');
			count++;
			if(count == 9){state = minus; count = 0;}
                        else if(input == 0x02){state = minus_down;}
                        else if(input == 0x01){state = plus;}
                        else if (input == 0x03){state = reset;}
                        else {state = initialize;}
                        break;
		case minus:
			state = minus_down;
			count = 0;
			break;
		default:
			state = initialize;
                        		break;
	}
	switch (state){	
		case Start:
		case Actual_start:
			output = 0;
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
			//count = 0;
			break;
		case minus:
			if(output > 0){output = output - 1;}
			//count = 0;
			break;
		default:
			output = 7;
                        break;
	}
//	count++;
	//LCD_DisplayString(1, output + ‘0’);
}
/*MAIN FUNCTION*/
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(100);
    	TimerOn();
	LCD_init();
    	while (1) {
		Tick();
		while(!TimerFlag) {};
		TimerFlag = 0;
   	 }
}

