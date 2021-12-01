/*	Author: sbala025 
 *	 *	Assignment: Final Project - Menu Component
 *	  *	Exercise Description: [optional - include for your own benefit]
 *	   *	Video: https://drive.google.com/drive/folders/1ygv6vqM5EPUE-t_Sg4Y_grqKhSv98EWi?usp=sharing
 *	    *	I acknowledge all content contained herein, excluding template or example
 *	     *	code, is my own original work.
 *	      */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#ifdef SIMULATE
#include "simAVRHeader.h"
#endif

unsigned char movement = 0;
enum Menu {Start, OFF, WELCOME, MESSAGE1, CHOOSE1, MESSAGE2, CHOOSE2, BEG1, BEG2, BEG3, BEG4, GAME} menu_state;
unsigned long time = 0;
unsigned char inputA = 0;
unsigned char inputD = 0;
/*INPUTS CHECK*/
unsigned char gameControl = 0;	
unsigned char light_output = 0;
/*PLAYER VARIABLES*/
unsigned char power1 = 0;
unsigned char power2 = 0;

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
void adc_init()
{
	ADMUX = (1<<REFS0);
	/* ADC Enable and prescaler of 128
 * 	   16000000/128 = 125000*/
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
	ch &= 0b00000111;  
	ADMUX = (ADMUX & 0xF8)|ch; 
	
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

unsigned char joystick1and2() {
	uint16_t y1 = adc_read(0);
	uint16_t y2 = adc_read(1);
	unsigned char joystick1 = 0;
	unsigned char joystick2 = 0;
	if (y1 >= 600){ 
		joystick1 = 1;
	}
	else if (y1 <= 512) { 
		joystick1 = 2;
	}
	else {
		joystick1 = 0;
	}
	if (y2 >= 600){ 
		joystick2 = 4;
	}
	else if (y2 <= 512) { 
		joystick2 = 8;
	}
	else {
		joystick2 = 0;
	}
	movement = joystick1 | joystick2;
	return movement;
}

void Menu() {
	inputA = ~PINA;
	inputD = ~PIND;
	gameControl = inputD & 0x01;
        uint16_t y = adc_read(0);
	uint16_t x = adc_read(1);
	switch(menu_state) {
	case Start:
		menu_state = OFF;
        case OFF:
	    if(gameControl == 0x01){menu_state = WELCOME;}
	    else{menu_state = OFF;}
            break;
       case WELCOME:
	    if(gameControl == 0x01){menu_state = OFF; time = 0;}
	    else if(time >= 3000){menu_state = MESSAGE1; time = 0;}
	    else{menu_state = WELCOME; time += 100;}
            break;
	case MESSAGE1:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 3000){menu_state = CHOOSE1; time = 0;}
	    else{menu_state = MESSAGE1; time += 100;}
            break;
	case CHOOSE1:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 6000){menu_state = MESSAGE2; time = 0;}
	    else{menu_state = CHOOSE1; time += 100;}
            break;
	case MESSAGE2:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 3000){menu_state = CHOOSE2; time = 0;}
	    else{menu_state = MESSAGE2; time += 100;}
            break;
	case CHOOSE2:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 6000){menu_state = BEG1; time = 0;}
	    else{menu_state = CHOOSE2; time += 100;}
            break;
	case BEG1:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 2500){menu_state = BEG2; time = 0;}
	    else{menu_state = BEG1; time += 100;}
            break;
	case BEG2:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 1000){menu_state = BEG3; time = 0;}
	    else{menu_state = BEG2; time += 100;}
            break;
	case BEG3:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 1000){menu_state = BEG4; time = 0;}
	    else{menu_state = BEG3; time += 100;}
            break;
	case BEG4:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 1000){menu_state = GAME;}
	    else{menu_state = BEG4; time += 100;}
            break;
	case GAME:
	    if(gameControl == 0x01){menu_state = WELCOME; time = 0;}
	    else if(time >= 20000){menu_state = WELCOME; time = 0;}
	    else{menu_state = BEG4; time += 100;}
            break;
	default:
		menu_state = WELCOME; break;
    }
    switch(menu_state){
	case Start:
		break;
        case OFF:
	    light_output = 0x10; break;
        case WELCOME:
            light_output = 0x0F;
	    power1 = 1;
	    power2 = 1; 
	    break;
	case MESSAGE1:
	    light_output = 0x03; break;
	case CHOOSE1:
	    if(y >= 600 && power1 == 1){power1 = 0x08;}
	    else if(y >= 600 && power1 != 1){power1 = power1 >> 1;}
	    else if(y <= 400 && power1 == 8){power1 = 0x01;}
	    else if(y <= 400 && power1 != 8){power1 = power1 << 1;}
	    light_output = power1;
	    break;
	case MESSAGE2:
	    light_output = 0x0C; break;
	case CHOOSE2:
	    if(x >= 600 && power2 == 1){power2 = 0x08;}
	    else if(x >= 600 && power2 != 1){power2 = power2 >> 1;}
	    else if(x <= 400 && power2 == 8){power2 = 0x01;}
	    else if(x <= 400 && power2 != 8){power2 = power2 << 1;}
	    light_output = power2;
	    break;
	case BEG1:
	    light_output = 0x01; break;
	case BEG2:
	    light_output = 0x03; break;
	case BEG3:
	    light_output = 0x07; break;
	case BEG4:
	    light_output = 0x0F; break;
	case GAME: 
	    light_output = 0x1F; break;
        default:
            break;
    }
	PORTC = light_output;
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0x0FF; PORTC = 0x00;
    DDRD = 0x00; PORTD = 0xFF;
    adc_init();
    TimerSet(100);
    TimerOn();
    menu_state = Start;
    while (1) { 
	Menu();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}
