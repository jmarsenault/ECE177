// Put a nice header here with your name, date, and lab description

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BUFFSIZE 16
// the following is provided in case it is needed in "getkey()" -- see class notes
#define nop() asm volatile("nop")

signed char getkey(void);			// forward declarations
signed char mapkey(signed char key);
char getpw(char maxsize, char pw[]); 	// Input keys into the array
char compareArrays(char size, const char a1[], const char a2[]);
void mydelayms(unsigned int ms);

void main(void) {
	char passwd[] = {1};			// Set the password in your function
	char pwsize = 1;
	char pwbuff[BUFFSIZE];

	//	DDRA = 0xF0; // While running the lower 4 bits of PORTA will be inputs and the
	// upper 4 bits will be outputs, but we'll make them outputs one at
	// a time, so we'll actually control the data direction in getkey(),
	// the keypad scanning routine.

	lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;

	// Your main code here
	while(1){
		 char x;
		x = getpw(pwsize, pwbuff);
		
		if((x==pwsize)&&(compareArrays(pwsize,passwd,pwbuff)==1)){
			printf("Open lock\n");
			mydelayms(2000);
			printf("\n \n \n \n \n \n \n \n");
		}
		
		else{
			printf("Error");
			mydelayms(500);
			printf("\n");
			printf("Error");
			mydelayms(500);
			printf("\n");
			printf("Error");
			mydelayms(500);
			printf("\n");
			printf("Error");
			mydelayms(500);
			printf("\n \n \n \n \n \n \n \n \n");
			
			
			
		}
		
		
		
	}

}

// getkey(), mapkey(), getpw(), compareArrays() and mydelayms() functions here
signed char getkey(){
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

signed char mapkey (signed char key) {
	if (key > 15 || key < 0) {
		return (-1);
	}
	else {
		unsigned char map[] = {1, 2, 3, 10, 4, 5, 6, 11, 7, 8, 9, 12, '*', 0, '#', 13};
		return map[key];
	}
}

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
	}
}
char getpw(char maxSize, char buffer[]) {

	char key;
	int i = 0;


	do {
		do {
		} while (getkey() != -1);
		do {
		} while ((key = mapkey(getkey())) == -1);

		if (key >= 0 && key <= 13 && i < maxSize) {
			buffer[i] = key;
			i += 1;
		}
		else if (key == '*') {
			if (i > 0) {
				i -= 1;
			}
		}
		
	} while (key != '#');
	
	return i;

}

char compareArrays(char size, const char a1[], const char a2[]) {
	int i;
	for (i = 0; i < size; i++) {
		
		if (a1[i] != a2[i]) {
			return 0;
		}
		
	}
	return 1;
}

void mydelayms(unsigned int ms){
	volatile int i,k;
	
	for(i=0;i<ms;i++){
		for(k=0;k<75;k++){}
	}
	
}