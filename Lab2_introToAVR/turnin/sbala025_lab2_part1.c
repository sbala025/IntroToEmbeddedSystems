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
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
    // Initialize output on PORTB to 0x00

				
    /* Insert your solution below */
    while (1) {
	PORTB = 0x0F;	// Writes port B's 8 pins with the values
				// on port A's 8 pins
    }
    return 1;
}
