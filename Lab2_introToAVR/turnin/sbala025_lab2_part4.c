/*	Author: sbala025
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2  Exercise - all of them
 *	Exercise Description: Learned how to use basic terminal and git command and the basics of AV
 *	R
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdlib.h>
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Configure A, B, and C */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
    DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
    DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs
   
    unsigned char inputA = PORTA; //initialize PORTA
    unsigned char inputB = PORTB; //initialize PORTB
    unsigned char inputC = PORTC; //initialize PORTC
    unsigned char balanced = 0x00; //initialize to zero 
    unsigned char limit = 0x00; //initialize to zero 
    unsigned short totalweight = 0x0000; // initialize totalweight
   				
    /* Insert your solution below */
    while(1){
        inputA = PINA;
	inputB = PINB;
	inputC = PINC;
	balanced = 0x00; //must always start at 0
	limit = 0x00; //must always start at 0
	totalweight = 0x00; // must always start at 0

	//Find total weight and reduce to 6 most important bits
	totalweight = inputA + inputB + inputC;

				
	//Check if total weight exceed max limit (140) --> D0
	if(totalweight > 140){
		limit = 0x01;
	}

	//Check if ride is balanced --> D1
	if(abs(inputA - inputB) > 0x8C){
		balanced = 0x02;
	}
	
	//Convert weight to be only six bits 0x0000 --> 0x00XX
	totalweight = (totalweight & 0x00FC)<<2;
	
	//Combine into one
	PORTD = totalweight | limit | balanced;	
    }
    return 1;
}
