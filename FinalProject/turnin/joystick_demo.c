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
unsigned char JoystickPos(unsigned char x, unsigned char y)}
void adc_init(){
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch){
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xF8)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}

unsigned short ADC_Scaler(unsigned short ADC_Max, unsigned short ADC_Val, unsigned char Divider)
{
    unsigned short count = ADC_Max / counter;
    unsigned char xy= 0x00;

	for(unsigned char index = 1; index <= counter; index++){
    		 if((ADC_Val <= index*count) && (ADC_Val >= (index-1)*count) ){
    			xy = index;
                 }
        }
        return xy;
}
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
 */
        if ((x == 2) && (y == 1)){
        	return 1;
    	}
    	else if ((x == 1) && (y == 2)){
        	return 2;
    	}
    	else if ((x == 2) && (y == 2)){
        	return 0;
    	}
    	else if ((x == 3) && (y == 2)){
        	return 4;
    	}
    	else if ((x == 2) && (y == 3)){
        	return 3;
    	}
	else{
		return 0;
	}
}
/*
 * 0 | 3 | 0
 * 2 | 0 | 4
 * 0 | 1 | 0
 */
/*---------------------------------------------------------------------------------------------------------------------------------------------*/

/*------Tick Function--------------------------------------------------------------------------------------------------------------------------*/
enum Joystick{Start, Light}pos;
unsigned char output = 0;
unsigned char xpos = 0;
unsigned char ypos = 0;
void Tick(){
	switch(pos){
	case Start:
		pos = Light; break;
	case Light:
		if(JoystickPos(xpos, ypos) == 1){ output = 0x01;}
		else if(JoystickPos(xpos, ypos) == 2){output = 0x02;}
		else if(JoystickPos(xpos, ypos) == 3){output = 0x04;}
		else if(JoystickPos(xpos, ypos) == 4){output = 0x08;}
		else{output = 0x00;}
	default:
		pos = Light; break; 	
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/

/*------Main Function--------------------------------------------------------------------------------------------------------------------------*/
int main(void) {
    	/* Insert DDR and PORT initializations */
	DDRA = 0x00; DDRA = 0xFF;
	DDRB = 0xFF; DDRB = 0x00;
    	/* Insert your solution below */
	TimerSet(1000);
	TimerOn();	 
   	while (1) {
		Tick();
		while(!TimerFlag) {};
		TimerFlag = 0;
    	}
    	return 1;
}
