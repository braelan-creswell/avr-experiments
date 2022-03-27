//Braelan Creswell 3/26/2018 "AVR PONG"

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <string.h>
#include <avr/wdt.h>
#include "lcd.h"
#include "keypad.h"
//Watchdog Timer Reset
#define soft_reset()        \
do                          \
{                           \
    wdt_enable(WDTO_15MS);  \
    for(;;)                 \
    {                       \
    }                       \
} while(0)

void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

// Disable Watchdog
void wdt_init(void)
{
    MCUSR = 0;
    wdt_disable();

    return;
}

//Set Variables
static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

#define LEFTMOST 0b0000000001
#define RIGHTMOST 0b1000000000

enum {left_serve, right_serve, moving_left, moving_right, rscore, lscore};

char state;
unsigned int leds;		// Current "court" --- inverse of PORTC
int right_score = 0, left_score = 0;
char winner[6] = {0};
char difficulty;
//Function Prototypes
void adjustLEDs(void);
void newstate(void);
void setLEDs(void);
void score(int side);

int main(void) {

	lcd_init();		// If you want to write to the LCD
	stdout=&lcd_stdout;

// Required setup for I/O pins
	DDRD = 0xFF;		// All PORTD pins are outputs
  DDRC|=_BV(PIN0)|_BV(PIN1); //Two PORTC pins are outputs

	state = left_serve;

	printf("Select Level\n");
	printf("(1-3)\n");
	difficulty = keypad_getkey();

//Loop Functios
	while(1) {
  	adjustLEDs(); //Set LEDs
  	newstate(); //Check State
		if(keypad_getkeynl() == '0') //Reset Button
		soft_reset();
		if(difficulty == '3')
		_delay_ms(60);
		if(difficulty == '2')
		_delay_ms(100);
		if(difficulty == '1')
		_delay_ms(200);
		else
		_delay_ms(100);
}


}		// end main

void newstate(void) {
	static int keypress = 0;
	if(keypress == 0) {
		if(keypad_getkeynl() == '1') { //Left Button
			keypress = 4;
			if(leds == LEFTMOST) {
				state = moving_right;
			}
			else {
				state = right_serve;
				score(rscore);
			}
		}
		if(keypad_getkeynl() == 'A') { //Right Button
			keypress = 4;
			if(leds == RIGHTMOST) {
				state = moving_left;
			}
			else {
				state = left_serve;
				score(lscore);
			}
		}
	}
		if(0b0000000000 == (leds & 0x3FF)) {
			if(state == moving_right) {
				state = left_serve;
				score(lscore);
			}
			else if(state == moving_left) {
				state = right_serve;
				score(rscore);
			}
	}
	if(keypress != 0)
	keypress -= 1;
	} //end newstate

  void adjustLEDs(void) {

    switch (state)  {
    case left_serve:
        leds=LEFTMOST;
				setLEDs();
        break;

    case right_serve:
        leds=RIGHTMOST;
				setLEDs();
        break;

    case moving_left:
				leds >>= 1;
				setLEDs();
        break;

    case moving_right:
				leds <<= 1;
				setLEDs();
        break;
      }
  } //end adjustLEDs

	void setLEDs(void) {
		PORTD =~ (leds & 0xFF);
		PORTC &= 0xFC;
		PORTC |= (~(leds >> 8) & 0x03);
	} //end setLEDs

	void score(int side) {
		lcd_init();
		stdout=&lcd_stdout;

		if(side == rscore)
		right_score += 1;
		if(side == lscore)
		left_score += 1;
		if(left_score == 15)
		strcpy(winner, "Left");
		if(right_score == 15)
		strcpy(winner, "Right");
		if(winner[1] != 0) {
		printf("%s Wins!\n", winner);
		printf("Press 0 to Reset\n");
		winner[1] = 0;
		}
		else {
			printf("Right Score: %d\n", right_score);
			printf("Left Score : %d\n", left_score);
		}
	}
