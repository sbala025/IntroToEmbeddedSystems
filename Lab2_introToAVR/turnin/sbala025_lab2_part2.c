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
    /* Configure A and C */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs
   
    //unsigned char input = PORTA; //initialize PORTA
    //unsigned char cntavail = 0x00; // initialize cntavail
   				
    /* Insert your solution below */
    while(1){
	 unsigned char input = PORTA; //initialize PORTA
    	 unsigned char cntavail = 0x00; // initialize cntavail
         input = PINA;
	 input = input &0x01;
         if(input == 0x00) {//every thing full
	      PORTC = cntavail+4;					
        }
	//three spots are full
	else if(input == 0x07 || input ==0x0B || input == 0x0D || input == 0x0E){ //three spots are full
	     PORTC = cntavail+1;
	}
	//two spots are full
	else if(input == 0x03 || input == 0x05 || input == 0x06 || input == 0x09 || input == 0x0A || input == 0x0C){ //two spots are full
    	     PORTC = cntavail+2;
	}
	//one spot is full
	else if (input == 0x01 || input == 0x02 || input == 0x04 || input == 0x08){//one spot is full
	     PORTC = cntavail+3;
	}
	else{
	     PORTC = cntavail;
	}
    }
    return 1;
}
