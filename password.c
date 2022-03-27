//Braelan Creswell

//overclocking #define F_CPU 8000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
//#include <util/delay.h>		// for delays
#include "keypad.h"
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BUFFSIZE 16

char getpw(char size, char *pw); 	// Input keys into the array
char compareArrays(char size, char array1[], char array2[]);
void mydelayms(unsigned int ms);
signed char keymap[16] = {1,2,3,'A',4,5,6,'B',7,8,9,'C','*',0,'#','D'};

char passwd[] = {1,5,9,'D'};			// Set the password in your function
char pwsize = 4;
char input[BUFFSIZE];
char size;
char buffer = BUFFSIZE;
char *pw = input;

void main(void) {


	lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;
	printf("Test");

 while(1) {
	 size = getpw(buffer, pw);
	 if(size == pwsize) {
		 printf("size");
		 if(compareArrays(size, input, passwd)){
			 printf("Open Lock");
			 mydelayms(2000);
			 //lcd_iwrite(LCD_CLR);
		 }
	 }
		 else {
			 printf("size");
			 /*lcd_iwrite(LCD_CLR);
			 mydelayms(250);
			 printf("Error");
			 mydelayms(250);
			 lcd_iwrite(LCD_CLR);
			 mydelayms(250);
			 printf("Error");
			 mydelayms(250);
			 lcd_iwrite(LCD_CLR);
			 mydelayms(250);
			 printf("Error");
			 mydelayms(250);
			 lcd_iwrite(LCD_CLR);
			 mydelayms(250);
			 printf("Error");
			 mydelayms(250);
			 lcd_iwrite(LCD_CLR);*/

		 }
	 }
 }


/*char getpw(char size, char *pw) {
    signed char keyraw;
    char key;
    char *i = pw;
    while(1) {
        while((keyraw = keypad_getkeyrawnl()) == -1);
        key = keypad_mapkey(keyraw, keymap);
				if(pw-i < size && pw-i >= 0) {
				if(key >= 0 && key < 15) {
					*pw = key;
					*pw++;
				lcd_iwrite(LCD_CLR);
				for(char *j = i; j<pw; *j++) {
					printf("*");
				}
				mydelayms(20);
        while(keypad_getkeyrawnl() != -1);

        }
        }
				if(key == '*' && pw-i > 0) {
						*pw--;
						lcd_iwrite(LCD_CLR);
						for(char *j = i; j<pw; *j++) {
							printf("*");
						}
						mydelayms(20);
            while(keypad_getkeyrawnl() != -1);
        }
        if(key == '#') {
					lcd_iwrite(LCD_CLR);
					return pw-i;
				}
    }
}*/

char getpw(char size, char *pw) {
    signed char keyraw;
    char key;
    char *i = pw;
    while(1) {
        while((keyraw = keypad_getkeyrawnl()) == -1);
        key = keypad_mapkey(keyraw, keymap);
        if(pw-i < size && pw-i >= 0) {
        if(key >= 0 && key < 15) {
        *pw = key;
        *pw++;
        while(keypad_getkeyrawnl() != -1);
        }
        }
        if(key == '*' && pw-i > 0) {
            *pw--;
            while(keypad_getkeyrawnl() != -1);
        }
        if(key == '#')
        return pw-i;
    }
}

char compareArrays(char size, char *array1, char *array2) {
    char *i = array1;
    while(array1-i<size) {
        if(*array1++ != *array2++)
        return 0;
    }
    return 1;
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
