//Braelan Creswell Lab 11

#define F_CPU 8000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
//#include <util/delay.h>		// for delays
#include "keypad.h"
#include "lcd.h"


static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

// The following defines are for the serial port (F_CPU, above, is also needed)
#define BAUD 9600
#define UBRR_SET (F_CPU / 8 / BAUD -1) // page 174
#define TOGGLESPEAKER PORTC^=0x01;


struct note {
	unsigned char notenum;		// index into array of frequencies for this note
	unsigned char duration;		// duration of note in 1/8ths of a second
};

struct song {
	unsigned char numnotes;		// Number of notes in this song
	const struct note thenotes[30];	// Array of the notes (max 30)
};

const struct song steinsong = {
    14,
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


const struct song marylamb = {
    26,
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

void delaycycles(unsigned int cycles);
void mydelayms(unsigned int ms);
void playnote(struct note n);
void playsong(const struct song s);
void serialInit(void);
unsigned char serialRead(void);
void serialWrite(unsigned char sendByte);

int main(void) {

  lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;

  TCCR1B  = 0x01;		// Enable Timer 1 to count normally using the internal clock
  DDRC|=_BV(PIN0); //Two PORTC pins are outputs
  DDRD=0xFF;
  TOGGLESPEAKER

  while(1) {
    char key = keypad_getkeyraw();
    if(key == 0)
    playsong(steinsong);
    if(key == 1)
    playsong(marylamb);
  }
}

void playnote(struct note n) {
  unsigned int delay = (F_CPU/2)/frequency[n.notenum];
  unsigned int toggle = (frequency[n.notenum]*n.duration)/8;
  for(int i = 0; i < toggle; i++) {
    TOGGLESPEAKER
    delaycycles(delay);
    TOGGLESPEAKER
    delaycycles(delay);
}
mydelayms(10);
}

void playsong(const struct song s) {
for(int i = 0; i < s.numnotes; i++) {
  playnote(s.thenotes[i]);
}
}

void delaycycles(unsigned int cycles) {
  //cycles += 10;
  TCNT1 = cycles * -1;
  TIFR1 = ((0x0001 << TOV1) | TIFR1);
  while((TIFR1 & (0x0001 << TOV1)) != (0x0001 << TOV1)){}
}

void mydelayms(unsigned int ms) {
volatile int i;
for(i = 0; i < ms; i++) {
  delaycycles(F_CPU/1000);
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
