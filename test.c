#define F_CPU 1000000UL
#define KEYPAD_TELPAD
#define KEYPAD_USEPORTA
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "lcd.h"
#include "keypad.h"


static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

int main(void)
{
	uint8_t i=0;
	uint16_t v=0;
	unsigned char O = 0;
	lcd_init();

	stdout=&lcd_stdout;


	PORTD=0xFF;
	DDRD=0xFF;
	DDRC|=_BV(PIN0)|_BV(PIN1);


	while (1) {
		for (i=0;i<10;i++) {
			if (i==0) {
				v=0x3FE;
			} else {
				v=(v<<1)|1;
			}
			PORTD=v&0xFF;
			if (v&0x0100) {
				PORTC|=_BV(PIN0);
			} else {
				PORTC&=~_BV(PIN0);
			}
			if (v&0x0200) {
				PORTC|=_BV(PIN1);
			} else {
				PORTC&=~_BV(PIN1);
			}

			_delay_ms(200);
		}
		//O = keypad_getkey();
		//printf("Key is %c\n", O);
	}
}
