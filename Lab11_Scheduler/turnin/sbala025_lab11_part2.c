/*	Author: sbala025
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	     
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
*/

/*-----INCLUDE STATEMENTS---------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#include <keypad.h>
#include <stdio.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LCDdisplay{text};

unsigned char output = 0x00;
unsigned char i = 0;

const unsigned char MAINTEXT[42] = {' ','C','S','1','2','0','B',' ','I','S',' ','L','E','G','E','N','D','.','.','.','W','A','I','T',' ','F','O','R',' ','I','T',' ','D','A','R','Y','!',' ',' ' ,' ',};

int D_Tick(int state){
	switch(state){
	case text:
		for(
	}
	return state;
}
