//Braelan Creswell 3/26/2018 "4x4 Keypad Library"
#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define PUSHED 1
#define COL_ONE ((PINA&_BV(PIN0)) >> 0)
#define COL_TWO ((PINA&_BV(PIN1)) >> 1)
#define COL_THREE ((PINA&_BV(PIN2)) >> 2)
#define COL_FOUR ((PINA&_BV(PIN3)) >> 3)
//#define ROW_ONE ((PINA&_BV(PIN4)) >> 4)
//#define ROW_TWO ((PINA&_BV(PIN5)) >> 5)
//#define ROW_THREE ((PINA&_BV(PIN6)) >> 6)
//#define ROW_FOUR ((PINA&_BV(PIN7)) >> 7)


unsigned char keypad_getkey(void);
unsigned char keypad_getkeynl(void);
signed char keypad_getkeyraw(void);
signed char keypad_getkeyrawnl(void);
signed char keypad_mapkey(signed char keys, signed char keymap[16]);

#include "keypad.c"
#endif
