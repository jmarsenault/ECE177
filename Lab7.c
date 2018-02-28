// Joseph Arsenault, 10-26-2016, Lab 7, PONG

#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

// Put your "#define" directives here.
// These "#defines" will allow you to say for example,
//	if (RIGHT_BUTTON == PUSHED) {do something}

#define PUSHED 1
#define RIGHT_BUTTON ((PINA&_BV(PIN3)) >> 3)
#define LEFT_BUTTON ((PINA&_BV(PIN0)) >> 0)

#define LEFTMOST 0b10000000
#define RIGHTMOST 0b00000001


int main(void) {
// put your "enum" for "left_serve", "right_serve", etc. here
enum states { left_serve, right_serve, moving_left, moving_right };


// Include the following variable declarations here
	char state;		// This variable holds the current state
	char leds;		// Current "court" --- inverse of PORTC

	lcd_init();		// If you want to write to the LCD
	stdout=&lcd_stdout;

// Required setup for I/O pins
	DDRD = 0xFF;		// All PORTD pins are outputs
	DDRA = 0x10;		// PORTA pin 4 is an output, rest inputs
	PORTA |= 0x10;		// Only pin 4 is important - should be 1

// Initialize "state" to "left_serve" here
	state = left_serve;


//
//  Your main code goes here - Simply put the body of the functions from CodeLab
//  here, that is, put code to adjust the "state", adjust the LED pattern, write
//  to the LEDs and delay into an infinite loop.

void newstate(void){

	if(LEFT_BUTTON == PUSHED){
			if(leds == LEFTMOST){
			state = moving_right;
			}
			else{
			state = right_serve;
			}
	}

	if (RIGHT_BUTTON == PUSHED){
			if(leds == RIGHTMOST){
				state = moving_left;
			}
			else{
				state = left_serve;
			}

	}

	if (RIGHT_BUTTON != PUSHED && LEFT_BUTTON!= PUSHED && leds == 0x00){
		if(state == moving_right){
			state = left_serve;
		}
		else {
			state = right_serve;
		}
	}
}

void adjustLEDs(void){
	switch(state){
		case moving_left :
		leds <<= 0x01;
		break;

		case moving_right:
		leds >>= 0x01;
		break;

		case right_serve:
		leds = RIGHTMOST;
		break;

		case left_serve:
		leds = LEFTMOST;
		break;
	}
}
void setLEDs(int  leds){
	PORTD = ~(leds & 0xFF);
	PORTC =  (((~leds)>>8)& 0x03) +	(PORTC & 0xFC);
}
//

}		// Don't forget this ending brace
