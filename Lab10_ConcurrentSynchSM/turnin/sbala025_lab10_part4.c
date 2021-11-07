/*	Author: sbala025
 *  	Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #10  Exercise #1
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

enum Three{Three_SMStart, T0, T1, T2}Three_State;
enum Blink{Blink_SMStart, Off, On}Blink_State;
enum Combine{Combine_SMStart, comb}Combine_State;
enum Speaker{Speaker_SMStart, S_Off, S_On}Speaker_State;
enum SpeakerSD{SpeakerSD_SMStart, Init, Up, Down}SpeakerUD_State;

unsigned char counter = 0x01;
unsigned char isOn = 0x00;
unsigned char three_output = 0x00;
unsigned char blink_output = 0x00;
unsigned char speaker_output = 0x00;
unsigned char speaker_counter = 0x00;
unsigned char output = 0x00;
unsigned char input = 0x00;
unsigned char frequencyCount[] = {1,2,3,4,5,6};

volatile unsigned char TimerFlag = 0;
/* Internal variables for mapping AVR’s ISR to our cleaner Timer ISR model */
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

 

void Tick_Three(){
	switch(Three_State){
		case Three_SMStart:
			Three_State = T0; break;
		case T0:
			Three_State = T1; break;
		case T1:
			Three_State = T2; break;
		case T2:
			Three_State = T0; break;
		default:
			Three_State = T0; break;
	}
	switch(Three_State){
                case Three_SMStart:
			break;
		case T0:
			three_output = 0x01; break;
		case T1:
			three_output = 0x02; break;
		case T2:
			three_output = 0x03; break;
		default:
			break;
	}
}

void Tick_Blink(){
	switch(Blink_State){
		case Blink_SMStart:
			Blink_State = Off; break;
		case Off:
			Blink_State = On; break;
		case On:
			Blink_State = Off;
		default:
			Blink_State = Off; break;
	}
	switch(Blink_State){
		case Blink_SMStart:
			break;
		case Off:
			blink_output = 0x00; break;
		case On: 
			blink_output = 0x01; break;
		default:
			break;
	}
}


void Tick_Speaker(){
	input = ~PINA & 0x04;
	switch(Speaker_State){
		case Speaker_SMStart:
			Speaker_State = S_Off; break;
		case S_Off:
			if(input == 0x04){Speaker_State = S_On;}
			else{Speaker_State = S_Off;} break;
		case S_On:
			if(input == 0x04){Speaker_State = S_On;}
                        else{Speaker_State = S_Off;} break;
		default:
			Speaker_State = S_Off; break;
	}
	switch(Speaker_State){
                case Speaker_SMStart:
			break;
		case S_Off:
			speaker_output = 0x00;
			speaker_counter = 0x00;
		case S_On:
			if(speaker_counter < frequencyCount[counter]){speaker_output == 0x10;}
			else if(speaker_counter < (2*frequencyCount[counter])){speaker_output == 0x00;}
			else{speaker_counter = 0x00;}
			speaker_counter++;
		default:
			break;
	}			
}

void Tick_SpeakerSD(){
	input = ~PINA & 0x03;
	switch (SpeakerSD_State){
		case SpeakerSD_SMStart:
			SpeakerSD_State = Init; break;
		case Init:
			if(input == 0x01){SpeakerSD_State = Up;}
			else if(input == 0x02){SpeakerSD_State = Down;}
			else{SpeakerSD_State = Init;}
			break;
		case Up:
			SpeakerSD_State = Init; break;
		case Down: 
			SpeakerSD_State = Init; break;
		default:
			SpeakerSD_State = Init; break;
	}
	switch (SpeakerSD_State){
		case SpeakerSD_SMStart:
			break;
		case Init:
			break;
		case Up:
			if(counter > 0){counter--;} break;
		case Down:
			if(counter < 5){counter++;} break;
		default:
			break;
	}	
}

void Tick_Combine(){
	switch(Combine_State){
		case Combine_SMStart:
			Combine_State = comb; break;
		case comb:
			Combine_State = comb; break;
		default:
			Combine_State = comb; break;
	}
	switch(Combine_State){
		case Combine_SMStart:
			break;
		case comb:
			output = blink_output | three_output | speaker_output; break;
		default:
			break;
	}
	PORTB = output;
}
int main(void) {
	/* Insert DDR and PORT initializations */
	DDRB = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    	/* Insert your solution below */
    	unsigned long Blink_Time = 0;
	unsigned long Three_Time = 0;
	const unsigned long TimerPeriod = 100;
	TimerSet(100);
	TimerOn();
	Three_State = Three_SMStart;
	Blink_State = Blink_SMStart;
	Combine_State = Combine_SMStart;
	while (1) {
		if(Three_Time >= 300){
			Tick_Three();
			Three_Time = 0;
		}if(Blink_Time >= 100){
			Tick_Blink();
			Blink_Time = 0;
		}
		Tick_Speaker();
		Tick_Combine();
		while(!TimerFlag){}
		TimerFlag = 0;
		Blink_Time += TimerPeriod;
		Three_Time += TimerPeriod;
    	}
 //   	return 1;
}
