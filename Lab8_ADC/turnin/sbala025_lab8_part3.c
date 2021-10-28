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

unsigned short my_short = 0x0000;
unsigned char my_char_upper = 0x00;
unsigned char my_char_lower = 0x00;

void ADC_init() {
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0XFF; PORTB = 0X00;
    //DDRD = 0XFF; PORTD = 0X00;
    /* Insert your solution below */
    ADC_init();
    while (1) {
        my_short = ADC;
        my_char_lower = (char)my_short;
        //my_char_upper = (char)my_short>>8;
        if(my_char_lower >= (0xFF/2)){PORTB = 0x01;}
        else{PORTB = 0x00;}
    }
    return 1;
}
