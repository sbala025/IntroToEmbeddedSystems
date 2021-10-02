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
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Configure A and B */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
    // Initialize output on PORTB to 0x00
    unsigned char input = 0x00; // Temp hold value of A
    //unsigned char output = 0x00; // Temp hold value of B
    input = PORTA;				
    /* Insert your solution below */
    while(1){
         input = PINA;
         if(input == 0x00) {
	      PORTC = 0x04;					
         }
	else if(input == 0x0D ||
    }
    return 1;
}
