// Put a nice header here with your name, date, and lab description

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays (but you'll write your own)
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BUFFSIZE 16

// the following is provided in case it is needed in "getkey()" -- see class notes
#define nop() asm volatile("nop")


signed char getkey(void);			// forward declarations
signed char mapkey(signed char key);
char getpw(char maxsize, char * const pw); 	// Input keys into the array
char compareArrays(char size, const char * const a1, const char * const a2);
void delaycycles(unsigned int cycles);
void mydelayms(unsigned int ms);

void main(void) {
	char passwd[] = {1};			// Hardcode the password here
	char pwsize = 1;
	char pwbuff[BUFFSIZE];


		DDRA = 0xF0; // While running the lower 4 bits of PORTA will be inputs and the
	// upper 4 bits will be outputs, but we'll make them outputs one at
	// a time, so we'll actually control the data direction in getkey(),
	// the keypad scanning routine.
	
	TCCR1B  = 0x01;		// Enable Timer 1 to count normally using the internal clock


	lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;
	
	// Your main code here
	while(1){
		char x;
		char t;
		//char t=5;
		
		x = getpw(pwsize, pwbuff);
		
		
		if((x==pwsize)&&(compareArrays(pwsize,pwbuff,passwd)==1)){
			printf("Open lock\n");
			mydelayms(2000);
			printf("\n \n \n \n \n \n \n \n \n ");
			
		}
		
		else {
			printf("Error");
			mydelayms(500);
			printf("\n \n \n \n \n \n \n \n \n");
				printf("Error");
				mydelayms(500);
				printf("\n \n \n \n \n \n \n \n \n");
					printf("Error");
					mydelayms(500);
					printf("\n \n \n \n \n \n \n \n \n");
						printf("Error");
						mydelayms(500);
						printf("\n \n \n \n \n \n \n \n \n");
						
			
	

			
		}
		
		
	}

}

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
char getpw(char maxsize, char *array){
	char hold = 1;
	char key = 0;
	char *ptr = array;
	do {
		do {
		} while (getkey() != -1);
		do {
		} while ((key = mapkey(getkey())) == -1);

		if (key >= 0 && key <= 13 && (ptr-array) < maxsize) {
			*ptr = key;
			ptr++;
		}
		else if (key == '*') {
			if ((ptr-array) > 0) {
				ptr--;
			}
		}
		
	} while (key != '#');
	
	return (ptr-array);
	
}
char compareArrays(char size, const char *array1, const char *array2){
	char *ptr1= array1;
	char *ptr2 = array2;
	char a = 1;
	for(ptr1= array1; (ptr1-array1)<size; ptr1++){
		if(*ptr1 != *ptr2){
			a=0;
		}
		ptr2++;
	}
	return a;
}

void mydelayms(unsigned int ms){
	volatile int i;
	for(i=0;i<ms;i++){
		delaycycles(1000);
	}
	
	}

void delaycycles(unsigned int cycles){
	TCNT1 = ~(cycles - 28);
	TIFR1 = 0x01<< TOV1;
	while(!(TIFR1&(0x01<<TOV1)));
		return;
		
	
}

// getkey(), mapkey(), getpw(), compareArrays(), delaycycles() and mydelayms() functions here