//Braelan Creswell 3/26/2018 "4x4 Keypad Library"
#include <avr/io.h>

unsigned char keypad_getkey(void) {

unsigned char out;


while (1) //loop key check forever
	{
		DDRA=0x10;
		PORTA |= 0x10;
		//Row 1 [1, 2, 3, A]
		if((COL_ONE && ROW_ONE) == PUSHED) {out = '1'; return out;}
		if((COL_TWO && ROW_ONE) == PUSHED) {out = '2'; return out;}
		if((COL_THREE && ROW_ONE) == PUSHED) {out = '3'; return out;}
		if((COL_FOUR && ROW_ONE) == PUSHED) {out = 'A'; return out;}

		DDRA=0x20;
		PORTA |= 0x20;
    //Row 2 [4, 5, 6, B]
		if((COL_ONE && ROW_TWO) == PUSHED) {out = '4'; return out;}
		if((COL_TWO && ROW_TWO) == PUSHED) {out = '5'; return out;}
		if((COL_THREE && ROW_TWO) == PUSHED) {out = '6'; return out;}
		if((COL_FOUR && ROW_TWO) == PUSHED) {out = 'B'; return out;}

		DDRA=0x40;
		PORTA |= 0x40;
		//Row 3 [7, 8, 9, C]
		if((COL_ONE && ROW_THREE) == PUSHED) {out = '7'; return out;}
		if((COL_TWO && ROW_THREE) == PUSHED) {out = '8'; return out;}
		if((COL_THREE && ROW_THREE) == PUSHED) {out = '9'; return out;}
		if((COL_FOUR && ROW_THREE) == PUSHED) {out = 'C'; return out;}

		DDRA=0x80;
		PORTA |= 0x80;
		//Row 4 [*, 0, #, D]
		if((COL_ONE && ROW_FOUR) == PUSHED) {out = '*'; return out;}
		if((COL_TWO && ROW_FOUR) == PUSHED) {out = '0'; return out;}
		if((COL_THREE && ROW_FOUR) == PUSHED) {out = '#'; return out;}
		if((COL_FOUR && ROW_FOUR) == PUSHED) {out = 'D'; return out;}

	}
      return out;
	}

	unsigned char keypad_getkeynl(void) {

	unsigned char out;

			DDRA=0x10;
			PORTA |= 0x10;
			//Row 1 [1, 2, 3, A]
			if((COL_ONE && ROW_ONE) == PUSHED) {out = '1'; return out;}
			if((COL_TWO && ROW_ONE) == PUSHED) {out = '2'; return out;}
			if((COL_THREE && ROW_ONE) == PUSHED) {out = '3'; return out;}
			if((COL_FOUR && ROW_ONE) == PUSHED) {out = 'A'; return out;}

			DDRA=0x20;
			PORTA |= 0x20;
	    //Row 2 [4, 5, 6, B]
			if((COL_ONE && ROW_TWO) == PUSHED) {out = '4'; return out;}
			if((COL_TWO && ROW_TWO) == PUSHED) {out = '5'; return out;}
			if((COL_THREE && ROW_TWO) == PUSHED) {out = '6'; return out;}
			if((COL_FOUR && ROW_TWO) == PUSHED) {out = 'B'; return out;}

			DDRA=0x40;
			PORTA |= 0x40;
			//Row 3 [7, 8, 9, C]
			if((COL_ONE && ROW_THREE) == PUSHED) {out = '7'; return out;}
			if((COL_TWO && ROW_THREE) == PUSHED) {out = '8'; return out;}
			if((COL_THREE && ROW_THREE) == PUSHED) {out = '9'; return out;}
			if((COL_FOUR && ROW_THREE) == PUSHED) {out = 'C'; return out;}

			DDRA=0x80;
			PORTA |= 0x80;
			//Row 4 [*, 0, #, D]
			if((COL_ONE && ROW_FOUR) == PUSHED) {out = '*'; return out;}
			if((COL_TWO && ROW_FOUR) == PUSHED) {out = '0'; return out;}
			if((COL_THREE && ROW_FOUR) == PUSHED) {out = '#'; return out;}
			if((COL_FOUR && ROW_FOUR) == PUSHED) {out = 'D'; return out;}

			out = 'F';
			return out;
		}

		unsigned char keypad_getkeyraw(void) {

		unsigned char out;

				DDRA=0x10;
				PORTA |= 0x10;
				//Row 1 [1, 2, 3, A]
				if((COL_ONE && ROW_ONE) == PUSHED) {out = 0; return out;}
				if((COL_TWO && ROW_ONE) == PUSHED) {out = 1; return out;}
				if((COL_THREE && ROW_ONE) == PUSHED) {out = 2; return out;}
				if((COL_FOUR && ROW_ONE) == PUSHED) {out = 3; return out;}

				DDRA=0x20;
				PORTA |= 0x20;
				//Row 2 [4, 5, 6, B]
				if((COL_ONE && ROW_TWO) == PUSHED) {out = 4; return out;}
				if((COL_TWO && ROW_TWO) == PUSHED) {out = 5; return out;}
				if((COL_THREE && ROW_TWO) == PUSHED) {out = 6; return out;}
				if((COL_FOUR && ROW_TWO) == PUSHED) {out = 7; return out;}

				DDRA=0x40;
				PORTA |= 0x40;
				//Row 3 [7, 8, 9, C]
				if((COL_ONE && ROW_THREE) == PUSHED) {out = 8; return out;}
				if((COL_TWO && ROW_THREE) == PUSHED) {out = 9; return out;}
				if((COL_THREE && ROW_THREE) == PUSHED) {out = 10; return out;}
				if((COL_FOUR && ROW_THREE) == PUSHED) {out = 11; return out;}

				DDRA=0x80;
				PORTA |= 0x80;
				//Row 4 [*, 0, #, D]
				if((COL_ONE && ROW_FOUR) == PUSHED) {out = 12; return out;}
				if((COL_TWO && ROW_FOUR) == PUSHED) {out = 13; return out;}
				if((COL_THREE && ROW_FOUR) == PUSHED) {out = 14; return out;}
				if((COL_FOUR && ROW_FOUR) == PUSHED) {out = 15; return out;}

				out = 0xFF;
				return out;
			}
