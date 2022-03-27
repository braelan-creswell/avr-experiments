#define F_CPU 1000000UL
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

void sound(unsigned char x);

int main(void)
{

  unsigned char key = 0;
	lcd_init();

	stdout=&lcd_stdout;


	DDRD=0xFF;
	//DDRC|=_BV(PIN0)|_BV(PIN1);
  printf("PRESS A KEY\n"); //displaying a string


  while(1)  {

    key = keypad_getkey();
    printf("Key Is %c\n", key);
    sound(key);


     }

     return 0;
   }

void sound(unsigned char x) {
  if(x == '1') {
  PORTD=0x00;
  for(int i = 0; i<100; i++) {}
  PORTD=0xFF;
  PORTD=0x00;
  _delay_ms(1);
  PORTD=0xFF;
}
if(x == '2') {
PORTD=0x00;
_delay_ms(2);
PORTD=0xFF;
}
if(x == '3') {
PORTD=0x00;
_delay_ms(3);
PORTD=0xFF;
}
if(x == 'A') {
PORTD=0x00;
_delay_ms(4);
PORTD=0xFF;
}
if(x == '4') {
PORTD=0x00;
_delay_ms(5);
PORTD=0xFF;
}

}
