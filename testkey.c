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

signed int getnum(void);
signed char mapkey(signed char keys);
unsigned char key = -1;
int output = 0;
char negative = ' ';

int main(void)
{
	lcd_init();
	stdout=&lcd_stdout;


	DDRD=0xFF;
  PORTD=0xFF;
	//DDRC|=_BV(PIN0)|_BV(PIN1);
  printf("PRESS A KEY\n"); //displaying a string
  while(1) {
    getnum();
    _delay_ms(100);
  }

}

signed int getnum(void) {
  static int keypress = 0;
  static int count = 0;
	if(keypress == 0) {
    key = keypad_getkeyraw();
    key = mapkey(key);

    if(key == 'A') {
      keypress = 4;
      if(negative == ' ')
      negative = '-';
      else if(negative == '-')
      negative = ' ';
      printf("\n%c%d\n",negative, output);
      printf(" \n");
    }
    if(key >= 0 && key <= 9) {
    keypress = 4;
    output *= 10;
    output += key;
    count++;
    printf("\n%c%d\n",negative, output);
    printf(" \n");

    }
    if(key == '*') {
      keypress = 4;
      output /= 10;
      count--;
      printf("\n%c%d\n",negative, output);
      printf(" \n");

    }
    if(key == '#') {
      keypress = 4;
      if((negative == '-') && (output * -1 < 0))
      output *= -1;
      printf("\n%d --> 0x%02X", output, output);
      PORTD=~output;
      output = 0;
      count = 0;
      negative = ' ';
    }
    if(count > 4) {
      printf("\nOverFlow");
      output = 0;
      count = 0;
      negative = ' ';
      _delay_ms(300);
      lcd_init();
    }
  }
  if(keypress != 0)
	keypress -= 1;
     return 0;
}

   signed char mapkey(signed char keys){
       signed char keymap[16] = {1,2,3,'A',4,5,6,'B',7,8,9,'C','*',0,'#','D'};
         if(keys >= 0 && keys <= 15) {
       return keymap[keys];
         }
         return -1;
   }
