

#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"


static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BAUD 9600
#define UBRR_SET (F_CPU / 8 / BAUD -1)


#define nop() asm volatile("nop")

#define TOGGLESPEAKER (PORTC ^= 0x02)


struct note {
	unsigned char notenum;		// index into array of frequencies for this note
	unsigned char duration;		// duration of note in 1/8ths of a second
};

struct song {
	unsigned char numnotes;		// Number of notes in this song
	const struct note thenotes[30];	// Array of the notes (max 30)
};

const struct song steinsong = {14,  // steinsong.numnotes
	{ // steinsong.thenotes
		//thenotes[notenum].duration
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
signed char mapkey(signed char key);
signed char getkey();
void delaycycles(unsigned int cycles);
void mydelayms(unsigned int ms);
void playnote(struct note n);
void playsong(const struct song* s);
void serialInit(void);
unsigned char serialRead(void);
void serialWrite(unsigned char sendByte);

/************************************************************************/

void main(){

	DDRC |= 0x02;
	PORTC = 0x00;

	lcd_init();
	stdout = &lcd_stdout;
	char key;
	int i;
			while(1){
				key=getnum();

		switch (key){
			case 1:
			//printf("play song");s
			playsong(marylamb);
			break;
			case 2:
			playsong (steinsong);
			break;
		}


			}

}
/************************************************************************/


void playnote(struct note n){
	int i, j, k;
	unsigned char currentnote = n.notenum;
	unsigned char length = n.duration;
	int freq = frequency[currentnote];
	int temp = (125000/freq)/2;
	for (i = 0; i < ((freq * length)/4); i++){
		

		TOGGLESPEAKER;
		
		for(j = 0; j < temp; j++){
			_delay_us(1);
		}

		
		
	}

}

void playsong(const struct song* s){
	int i, j, k;

	for (i = 0; i < s->numnotes; i++){

		playnote(s->thenotes[i]);
		mydelayms(10);

	}


}

void mydelayms(unsigned int ms){
	int l;
	for (l = 0; l < ms; l++){
		_delay_ms(1);
	}
}

signed char mapkey(signed char key){
	int x;
	unsigned char keys[16] ={1, 2, 3, 10, 4, 5, 6, 11, 7, 8, 9, 12, '*', 0, '#', 13};
	if (((key) > -1) && ((key) < 16)) {
		return keys[key];
	}
	else {
		return -1;
	}
}

signed char getkey() {
	int row, col;
	int mask1 = 0x10;
	int mask2;
	
	for(row = 0; row < 4; row++) {
		DDRA = mask1;
		PORTA = mask1;
		
		mask1 <<= 1;
		mask2 = 0x01;
		for (col=0; col < 4; col++) {
			if(PINA&mask2) {
				return ((4*row)+col);
			}
			mask2 <<= 1;
		}
	}
	return -1;
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