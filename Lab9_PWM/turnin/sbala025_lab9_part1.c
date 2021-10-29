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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Initial, C, D, E} state;
unsigned char input = 0x00;

//TIMER FUNCTIONS AND VARIABLES
volatile unsigned char TimerFlag = 0;
void TimerISR(){ TimerFlag = 1;}
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn(){
     TCCR1B = 0x0B;
     OCR1A = 125;
     TIMSK1 = 0x02;
     TCNT1 = 0;
     _avr_timer_cntcurr = _avr_timer_M;
     SREG |= 0x80;
}
void TimerOff() {TCCR1B = 0x00;}
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

//PWM FUNCTIONS AND VARIABLES
void set_PWM(double frequency) {
    static double current_frequency;
    if (frequency != current_frequency) {
        if (!frequency) { TCCR3B &= 0x08; }
        else { TCCR3B |= 0x03; }
        if (frequency < 0.954) { OCR3A = 0xFFFF; }
        else if (frequency > 31250) { OCR3A = 0x0000; }
        else { OCR3A = (short) (8000000 / (128 * frequency)) -1; }
        TCNT3 = 0;
        current_frequency = frequency;
    }
}
void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}
void PWM_off(){
    TCCR3A = 0X00;
    TCCR3B = 0X00;
}

//TICK FUNCTION
void Tick(){
    input = ~PINA & 0x07;
    switch(state){
	case Start:
	    state = Initial; break;
	case Initial:
	    if(input == 0x01){state = C;}
	    else if(input == 0x02){state = D;}
	    else if(input == 0x04){state = E;}
	    else{state = Initial;} break;
	case C:
	    if(input == 0x01){state = C;}
	    else{state = Initial;} break;
	case D:
	    if(input == 0x02){state = D;}
	    else{state = Initial;} break;
	case E:
	    if(input == 0x04){state = E;}
	    else{state = Initial;} break;
	default:
	    state = Initial; break;
    }
    switch(state){
	case Start: break;
	case Initial: set_PWM(0); break;
	case C: set_PWM(261.63); break;
	case D: set_PWM(293.66); break;
	case E: set_PWM(329.63); break;
	default: break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0X00; PORTA = 0XFF;
    DDRB = 0XFF; PORTB = 0X00; //AUTOMATICALLY CONNECTS TO PORTB6
    TimerSet(100); TimerOn();
    PWM_on();
    /* Insert your solution below */
    while (1) {
        Tick();
        while(!TimerFlag){};
        TimerFlag = 0;
    }
    //PWM_off();
    return 1;
}
