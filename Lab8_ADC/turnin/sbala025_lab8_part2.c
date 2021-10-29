/*	Author: sbala025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *      Video: https://drive.google.com/drive/folders/1TFTQVNYBFSkwfeAfD7Xym1YvXfrMgYn8?usp=sharing
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
    DDRD = 0XFF; PORTD = 0X00;
    /* Insert your solution below */
    ADC_init();
    while (1) {
    my_short = ADC;
    my_char_lower = (char)my_short;
    my_char_upper = (char)my_short>>8;
    PORTB = my_char_lower;
    PORTD = my_char_upper;
    }
    return 1;
}
