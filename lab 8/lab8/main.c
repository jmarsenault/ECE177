// Put a nice header here with your name, date, and lab description

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"

// the following is provided in case it is needed in "getkey()" -- see class notes
#define nop() asm volatile("nop")

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


signed char getkey(void);			// forward declarations
signed char mapkey(signed char);
signed int getnum(void);

void main(void) {
	signed char x;
	//	DDRA = 0xF0; // While running the lower 4 bits of PORTA will be inputs and the
	// upper 4 bits will be outputs, but we'll make them outputs one at
	// a time, so we'll actually control the data direction in getkey(),
	// the keypad scanning routine.

	lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;

	// Main code goes here
	while(1){
	x = getnum();
	printf("%d -> 0x%x\n", x, x);
	}

}


signed char getkey(void) {
	int i;
	int k;
	int mask = 0x10;
	int mask2 = 0x01;
	
	for (i = 0; i < 4; i++) {
		DDRA = mask;
		PORTA = mask;
		
		mask <<= 1;
		
		int mask2 = 0x01;
		for (k = 0; k < 4; k++) {
			if (PINA & mask2) {
				return (4 * i + k);
			}
			mask2 <<= 1;
		}
	}
	return (-1);
	
}
	// This routine will get a key on the keypad and will return the key number
	// below, or -1 if no key is pressed.
	// Keys are numbered top to bottom and left to right and the keypad is mapped
	// as follows

	//             PORTA
	//             Output	Key                 KEY
	//             Bits     Number            LABELING
	//              4 |  0  1  2  3        | 1  2  3  A
	//              5 |  4  5  6  7        | 4  5  6  B
	//              6 |  8  9 10 11        | 7  8  9  C
	//              7 | 12 13 14 15        | *  0  #  D
	//                 ------------         ------------
	//                   0  1  2  3
	//                PORTA Input Bits



	signed char mapkey(signed char key) {
			if (key > 15 || key < 0) {
				return (-1);
			}
			else {
				unsigned char map[] = {1, 2, 3, 10, 4, 5, 6, 11, 7, 8, 9, 12, '*', 0, '#', 13};
				return map[key];
			}
		}
		//	Return the mapping of the given key according to the following

		//             PORTA
		//             Output	Key                 KEY
		//             Bits     Number            LABELING
		//              4 |  0  1  2  3        | 1  2  3  A
		//              5 |  4  5  6  7        | 4  5  6  B
		//              6 |  8  9 10 11        | 7  8  9  C
		//              7 | 12 13 14 15        | *  0  #  D
		//                 ------------         ------------
		//                   0  1  2  3
		//                PORTA Input Bits



		signed int getnum(void) {
			int result = 0;
			char key;
			while (1) {
				while (getkey() != -1) {}
				while ((key = mapkey(getkey())) == -1) {}
				
				if (key >= 0 && key <= 9) {
					result = result * 10 + key;
				}
				else if (key == '*') {
					result /= 10;
				}
				else if (key == '#') {
					return result;
				}
				else if(key == 'A'){
					result = result * -1;
					return result;
				}
			}
		}
			// Calls getkey() multiple times and returns a multiple digit number.
			// E.g., If '1' then '2' then '3' then '#' are pressed, then the return value is 123.
			// Pressing '*' acts as a backspace.
			// Letters ('A', 'B', 'C', 'D') are ignored.

