/*
 */



// Put a nice header here with your name, date, and lab description
#define TOGGLESPEAKER (PORTC ^= 0x02)
#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"


static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

// The following defines are for the serial port (F_CPU, above, is also needed)
#define BAUD 9600
#define UBRR_SET (F_CPU / 8 / BAUD -1) // page 174

// the following is provided in case it is needed in "getkey()" -- see class notes
#define nop() asm volatile("nop")


struct note {
	unsigned char notenum;		// index into array of frequencies for this note
	unsigned char duration;		// duration of note in 1/8ths of a second
};

struct song {
	unsigned char numnotes;		// Number of notes in this song
	const struct note thenotes[30];	// Array of the notes (max 30)
};

const struct song steinsong = {14,
	{
		{2,12},	//	 First line of "Maine Stein Song"
		{4,1},	//	 Data is note number and duration (1/8 ths second)
		{2,3},
		{1,1},
		{2,3},
		{7,4},
		{11,8},
		{14,4},
		{7,2},
		{7,2},
		{9,4},
		{7,4},
		{6,8},
		{4,8}
	}
};


const struct song marylamb = {26,
	{
		{4,3},	//	 First line of "Mary Had a Little Lamb"
		{2,1},	//	 Data is note number and duration (1/8 ths second)
		{0,2},
		{2,2},
		{4,2},
		{4,2},
		{4,4},
		{2,2},
		{2,2},
		{2,4},
		{4,2},
		{7,2},
		{7,4},
		{4,3},
		{2,1},
		{0,2},
		{2,2},
		{4,2},
		{4,2},
		{4,2},
		{4,2},
		{2,2},
		{2,2},
		{4,2},
		{2,2},
		{0,8}
	}
};

const unsigned int frequency[] = {        // note number & note
		262,      // 0  C
		277,      // 1  C#
		294,      // 2  D
		311,      // 3  D#
		330,      // 4  E
		349,      // 5  F
		370,      // 6  F#
		392,      // 7  G
		415,      // 8  G#
		440,      // 9  A
		466,      // 10 A#
		494,      // 11 B
		523,      // 12 C
		554,      // 13 C#
		587       // 14 D
};

void mydelayms(unsigned int ms);

void delaycycles(unsigned int cycles);
void playnote(struct note n);
void playsong(const struct song* s);
void serialInit(void);
unsigned char serialRead(void);
void serialWrite(unsigned char sendByte);

/************************************************************************/
//		main() goes here
/************************************************************************/
//getkey() goes here.
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



void main(){
	char x=0;
		
		DDRC |= 0x02;
TCCR1B  = 0x01;
lcd_init();		// Init the LCD display
stdout=&lcd_stdout;
PORTC = 0x00;

        while(1){
			x = getnum();
			printf("%d\n",x);

            if(x==5){
				playsong(&marylamb);

            }
			if(x==6){
				playsong(&steinsong);
			}


        }







}

void serialInit(void) {
// set BAUD rate to 9600
	UCSR0A |= 1<<U2X0; 		// Set transmission speed
	UBRR0H = UBRR_SET>>8;	// load the upper UBRR bits
	UBRR0L = UBRR_SET;		// load lower bits. set the things in accordance with page 194

	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);	// set 8-bit data
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);	// enable rx and tx
}

unsigned char serialRead(void) {
//	Your code here
}

void serialWrite(unsigned char sendByte) {
//	Your code here
}
void playnote(struct note n){
	unsigned int toggle =0;
	unsigned int cycles =0;
	int i;
	toggle = frequency[n.notenum] * n.duration/8;
	cycles = 500000 / frequency[n.notenum];
	for(i=0;i<toggle;i++){
		TOGGLESPEAKER;
		delaycycles(cycles);
		TOGGLESPEAKER;
		delaycycles(cycles);
		mydelayms(10);

	}
}
	void delaycycles(unsigned int cycles){
		TCNT1 = ~(cycles - 28);
		TIFR1 = 0x01<< TOV1;
		while(!(TIFR1&(0x01<<TOV1)));
		return;
}
void playsong(const struct song* s){
	int i;
	for(i=0;i<s->numnotes; i++){
		playnote(s->thenotes[i]);
	}
	return;
}
	
	void mydelayms(unsigned int ms){
		volatile int i;
		for(i=0;i<ms;i++){
			delaycycles(1000);
		}
		
	}
	