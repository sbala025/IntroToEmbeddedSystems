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

enum States {Start, BEGIN, OFF, LED, PAUSE, RIGHT, LEFT} state;
volatile unsigned char TimerFlag = 0;
/* Internal variables for mapping AVR’s ISR to our cleaner Timer ISR model */
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char switchDirection = 0x00;
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

void Tick() {
	unsigned char input = ~PINA & 0X01;
	switch(state) {
		case Start:	
			state = BEGIN; 
			break;
		case BEGIN:
			State = OFF;
			break;
		case OFF:	
			state = NextLed; 
			break;
		case LED:	
			if (input == 0x01) {state = PAUSE;}
			else {state = LED;}break;
		case PAUSE:	
			if (input == 0x01) {state = PAUSE;}
			else {state = LED;}break;
		default:	
			state = Start; 
			break;
	}
	switch (state) {
		case Start:     
			break;
		case BEGIN:
			count = 5;
			break; 
               	case OFF:      
			PORTB = 0x01; 
			break;
		case LED:
		if (switchDirection == 0x00 && (output == 0x02)) {
			output = output >> 1;
			switchDirection = 0x01;
		}else if(switchDirection == 0x00 && (output != 0x02)) {
			output = output << 1;
		}else if(switchDirection == 0x01 && (output == 0x00)){
			output = output << 1;
                        switchDirection = 0x00;
		}else if(switchDirection == 0x01 && (output != 0x00)){
                        output = output >> 1;
		}
			break;
		case PAUSE: 	
			if(PORTB == 0x01){ count++;}
			else {count--;}
			break;
                default:        
			break;
	}
	if (count == 0x00) {LCD_DisplayString(1, 0 + ‘0’);}
	else if (count == 0x01) {LCD_DisplayString(1, 1 + ‘0’);}
	else if (count == 0x02) {LCD_DisplayString(1, 2 + ‘0’); }
	else if (count == 0x03) {LCD_DisplayString(1, 3 + ‘0’);}
	else if (count == 0x04) {LCD_DisplayString(1, 4 + ‘0’); }
	else if (count == 0x05) {LCD_DisplayString(1, 5 + ‘0’);}
	else if (count == 0x06) {LCD_DisplayString(1, 6 + ‘0’);}
	else if (count == 0x07) {LCD_DisplayString(1, 7 + ‘0’); }
	else if (count == 0x08) {LCD_DisplayString(1, 8 + ‘0’);}
	else if (count == 0x09) {LCD_DisplayString(1, 9 + ‘0’);}
}

void main(void) {
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xFF; PORTC = 0x00;
 DDRD = 0xFF; PORTD = 0x00;
 TimerSet(300);
  TimerOn();
  LCD_init();
  while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
  }
}

