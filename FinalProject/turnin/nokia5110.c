/*	Author: sbala025 
 *	 *	Assignment: Final Project - Menu Component
 *	  *	Exercise Description: [optional - include for your own benefit]
 *	   *	Video: https://drive.google.com/drive/folders/1ygv6vqM5EPUE-t_Sg4Y_grqKhSv98EWi?usp=sharing
 *	    *	I acknowledge all content contained herein, excluding template or example
 *	     *	code, is my own original work.
 *	      */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
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

/*-----NOKIA5110---------------------------------------------------------------------------------------------------------*/
#define PORT_LCD PORTB
#define DDR_LCD DDRB

#define LCD_SCE PB1
#define LCD_RST PB2
#define LCD_DC PB3
#define LCD_DIN PB4
#define LCD_CLK PB5

#define LCD_CONTRAST 0x40
const uint8_t CHARSET[][5] PROGMEM = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, 
	{ 0x00, 0x00, 0x5f, 0x00, 0x00 }, 
	{ 0x00, 0x07, 0x00, 0x07, 0x00 }, 
	{ 0x14, 0x7f, 0x14, 0x7f, 0x14 }, 
	{ 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, 
	{ 0x23, 0x13, 0x08, 0x64, 0x62 }, 
	{ 0x36, 0x49, 0x55, 0x22, 0x50 }, 
	{ 0x00, 0x05, 0x03, 0x00, 0x00 }, 
	{ 0x00, 0x1c, 0x22, 0x41, 0x00 }, 
	{ 0x00, 0x41, 0x22, 0x1c, 0x00 }, 
	{ 0x14, 0x08, 0x3e, 0x08, 0x14 }, 
	{ 0x08, 0x08, 0x3e, 0x08, 0x08 }, 
	{ 0x00, 0x50, 0x30, 0x00, 0x00 }, 
	{ 0x08, 0x08, 0x08, 0x08, 0x08 }, 
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, 
	{ 0x20, 0x10, 0x08, 0x04, 0x02 }, 
	{ 0x3e, 0x51, 0x49, 0x45, 0x3e }, 
	{ 0x00, 0x42, 0x7f, 0x40, 0x00 }, 
	{ 0x42, 0x61, 0x51, 0x49, 0x46 }, 
	{ 0x21, 0x41, 0x45, 0x4b, 0x31 },
	{ 0x18, 0x14, 0x12, 0x7f, 0x10 }, 
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, 
	{ 0x3c, 0x4a, 0x49, 0x49, 0x30 }, 
	{ 0x01, 0x71, 0x09, 0x05, 0x03 }, 
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, 
	{ 0x06, 0x49, 0x49, 0x29, 0x1e }, 
	{ 0x00, 0x36, 0x36, 0x00, 0x00 }, 
	{ 0x00, 0x56, 0x36, 0x00, 0x00 }, 
	{ 0x08, 0x14, 0x22, 0x41, 0x00 }, 
	{ 0x14, 0x14, 0x14, 0x14, 0x14 }, 
	{ 0x00, 0x41, 0x22, 0x14, 0x08 }, 
	{ 0x02, 0x01, 0x51, 0x09, 0x06 }, 
	{ 0x32, 0x49, 0x79, 0x41, 0x3e }, 
	{ 0x7e, 0x11, 0x11, 0x11, 0x7e }, 
	{ 0x7f, 0x49, 0x49, 0x49, 0x36 }, 
	{ 0x3e, 0x41, 0x41, 0x41, 0x22 }, 
	{ 0x7f, 0x41, 0x41, 0x22, 0x1c }, 
	{ 0x7f, 0x49, 0x49, 0x49, 0x41 }, 
	{ 0x7f, 0x09, 0x09, 0x09, 0x01 }, 
	{ 0x3e, 0x41, 0x49, 0x49, 0x7a }, 
	{ 0x7f, 0x08, 0x08, 0x08, 0x7f }, 
	{ 0x00, 0x41, 0x7f, 0x41, 0x00 }, 
	{ 0x20, 0x40, 0x41, 0x3f, 0x01 }, 
	{ 0x7f, 0x08, 0x14, 0x22, 0x41 }, 
	{ 0x7f, 0x40, 0x40, 0x40, 0x40 }, 
	{ 0x7f, 0x02, 0x0c, 0x02, 0x7f }, 
	{ 0x7f, 0x04, 0x08, 0x10, 0x7f }, 
	{ 0x3e, 0x41, 0x41, 0x41, 0x3e }, 
	{ 0x7f, 0x09, 0x09, 0x09, 0x06 }, 
	{ 0x3e, 0x41, 0x51, 0x21, 0x5e }, 
	{ 0x7f, 0x09, 0x19, 0x29, 0x46 }, 
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, 
	{ 0x01, 0x01, 0x7f, 0x01, 0x01 }, 
	{ 0x3f, 0x40, 0x40, 0x40, 0x3f }, 
	{ 0x1f, 0x20, 0x40, 0x20, 0x1f }, 
	{ 0x3f, 0x40, 0x38, 0x40, 0x3f }, 
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, 
	{ 0x07, 0x08, 0x70, 0x08, 0x07 }, 
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, 
	{ 0x00, 0x7f, 0x41, 0x41, 0x00 }, 
	{ 0x02, 0x04, 0x08, 0x10, 0x20 }, 
	{ 0x00, 0x41, 0x41, 0x7f, 0x00 }, 
	{ 0x04, 0x02, 0x01, 0x02, 0x04 }, 
	{ 0x40, 0x40, 0x40, 0x40, 0x40 }, 
	{ 0x00, 0x01, 0x02, 0x04, 0x00 }, 
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, 
	{ 0x7f, 0x48, 0x44, 0x44, 0x38 }, 
	{ 0x38, 0x44, 0x44, 0x44, 0x20 }, 
	{ 0x38, 0x44, 0x44, 0x48, 0x7f }, 
	{ 0x38, 0x54, 0x54, 0x54, 0x18 }, 
	{ 0x08, 0x7e, 0x09, 0x01, 0x02 }, 
	{ 0x0c, 0x52, 0x52, 0x52, 0x3e }, 
	{ 0x7f, 0x08, 0x04, 0x04, 0x78 }, 
	{ 0x00, 0x44, 0x7d, 0x40, 0x00 }, 
	{ 0x20, 0x40, 0x44, 0x3d, 0x00 }, 
	{ 0x7f, 0x10, 0x28, 0x44, 0x00 }, 
	{ 0x00, 0x41, 0x7f, 0x40, 0x00 }, 
	{ 0x7c, 0x04, 0x18, 0x04, 0x78 }, 
	{ 0x7c, 0x08, 0x04, 0x04, 0x78 }, 
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, 
	{ 0x7c, 0x14, 0x14, 0x14, 0x08 }, 
	{ 0x08, 0x14, 0x14, 0x18, 0x7c }, 
	{ 0x7c, 0x08, 0x04, 0x04, 0x08 }, 
	{ 0x48, 0x54, 0x54, 0x54, 0x20 }, 
	{ 0x04, 0x3f, 0x44, 0x40, 0x20 }, 
	{ 0x3c, 0x40, 0x40, 0x20, 0x7c }, 
	{ 0x1c, 0x20, 0x40, 0x20, 0x1c }, 
	{ 0x3c, 0x40, 0x30, 0x40, 0x3c }, 
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, 
	{ 0x0c, 0x50, 0x50, 0x50, 0x3c }, 
	{ 0x44, 0x64, 0x54, 0x4c, 0x44 }, 
	{ 0x00, 0x08, 0x36, 0x41, 0x00 }, 
	{ 0x00, 0x00, 0x7f, 0x00, 0x00 }, 
	{ 0x00, 0x41, 0x36, 0x08, 0x00 }, 
	{ 0x10, 0x08, 0x08, 0x10, 0x08 }, 
	{ 0x00, 0x00, 0x00, 0x00, 0x00 } 
};

static struct {
    uint8_t screen[504];
    uint8_t cursor_x;
    uint8_t cursor_y;
} nokia_lcd = {
    .cursor_x = 0,
    .cursor_y = 0
};


static void write(uint8_t b, uint8_t r_s)
{
	register uint8_t i;
	PORT_LCD &= ~(1 << LCD_SCE);
	/*recieve commands*/
	if (r_s)
		PORT_LCD |= (1 << LCD_DC);
	/*send commands*/
	else
		PORT_LCD &= ~(1 << LCD_DC);
	for (i = 0; i < 8; i++) {
		if ((b >> (7-i)) & 0x01)
			PORT_LCD |= (1 << LCD_DIN);
		else
			PORT_LCD &= ~(1 << LCD_DIN);
		PORT_LCD |= (1 << LCD_CLK);
		PORT_LCD &= ~(1 << LCD_CLK);
	}
	PORT_LCD |= (1 << LCD_SCE);
}

static void write_cmd(uint8_t cmd)
{
	write(cmd, 0);
}

static void write_data(uint8_t data)
{
	write(data, 1);
}

void nokia_init(void){
	register unsigned i;
	/* Set pins as output */
	DDR_LCD |= (1 << LCD_SCE);
	DDR_LCD |= (1 << LCD_RST);
	DDR_LCD |= (1 << LCD_DC);
	DDR_LCD |= (1 << LCD_DIN);
	DDR_LCD |= (1 << LCD_CLK);

	/* Reset display */
	PORT_LCD |= (1 << LCD_RST);
	PORT_LCD |= (1 << LCD_SCE);
	_delay_ms(10);
	PORT_LCD &= ~(1 << LCD_RST);
	_delay_ms(70);
	PORT_LCD |= (1 << LCD_RST);

	/*
 * 	 * Initialize display
 * 	 	 */
	/* Enable controller */
	PORT_LCD &= ~(1 << LCD_SCE);
	/* -LCD Extended Commands mode- */
	write_cmd(0x21);
	/* LCD bias mode 1:48 */
	write_cmd(0x13);
	/* Set temperature coefficient */
	write_cmd(0x06);
	/* Default VOP (3.06 + 66 * 0.06 = 7V) */
	write_cmd(0xC2);
	/* Standard Commands mode, powered down */
	write_cmd(0x20);
	/* LCD in normal mode */
	write_cmd(0x09);

	/* Clear LCD RAM */
	write_cmd(0x80);
	write_cmd(LCD_CONTRAST);
	for (i = 0; i < 504; i++)
		write_data(0x00);

	/* Activate LCD */
	write_cmd(0x08);
	write_cmd(0x0C);
}

void clear(void)
{
	register unsigned i;
	write_cmd(0x80);
	write_cmd(0x40);
	nokia_lcd.cursor_x = 0;
	nokia_lcd.cursor_y = 0;
	for(i = 0;i < 504; i++)
		nokia_lcd.screen[i] = 0x00;
}

void nokia_lcd_power(uint8_t on)
{
	write_cmd(on ? 0x20 : 0x24);
}

void nokia_pixel(uint8_t x, uint8_t y, uint8_t pix_location)
{
	uint8_t *byte = &nokia_lcd.screen[y/8*84+x];
	if (pix_location)
		*byte |= (1 << (y % 8));
	else
		*byte &= ~(1 << (y %8 ));
}

void nokia_write(uint8_t x, uint8_t y, const char *str)
{
	register uint8_t a, b;
	char temp = 0;
	nokia_lcd.cursor_x = x;
	nokia_lcd.cursor_y = y;
	while(*str)
	{
		temp = *str++;
		for (a = 0; a < 5; a++)
			for (b = 0; b < 7; b++)
				if (pgm_read_byte(&CHARSET[temp-32][a]) & (1 << b))
				nokia_pixel(nokia_lcd.cursor_x + a, nokia_lcd.cursor_y + b, 1);
				else
				nokia_pixel(nokia_lcd.cursor_x + a, nokia_lcd.cursor_y + b, 0);

		nokia_lcd.cursor_x += 5 + 1;
		if (nokia_lcd.cursor_x >= 84) {
			nokia_lcd.cursor_x = 0;
			nokia_lcd.cursor_y += 7 + 1;
		}
		if (nokia_lcd.cursor_y >= 48) {
			nokia_lcd.cursor_x = 0;
			nokia_lcd.cursor_y = 0;
		}
	}
}

void nokia_lcd_render(void)
{
	register unsigned i;
	/* Set column and row to 0 */
	write_cmd(0x80);
	write_cmd(0x40);

	/* Write screen to display */
	for (i = 0; i < 504; i++)
		write_data(nokia_lcd.screen[i]);
}

/*-----TIMER-----------------------------------------------------------------------------------------------------------*/
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

/*-----JOYSTICK---------------------------------------------------------------------------------------------------------*/
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
    nokia_init();
    clear();
    nokia_write(0,0,"IT'S WORKING!");
    /*nokia_lcd_set_cursor(0, 10);*/
    nokia_write(0,10,"Nice!");
    nokia_lcd_render();
    menu_state = Start;
    while (1) { 
	Menu();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}
