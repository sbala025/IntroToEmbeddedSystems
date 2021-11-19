#include <avr/io.h>
#include "io.h"

int main(void)
{
	DDRC = 0x00; 0xFF;
	DDRB = 0x00; 0xFF;

	LCD_init();
	LCD_DisplayString(1, "Hello World");

	while(1){continue;}
}
