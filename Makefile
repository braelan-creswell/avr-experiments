OBJS=${T}.o
CPU=atmega324a

CFLAGS=-funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing -fno-split-wide-types -Wall -Wstrict-prototypes -std=gnu99 -MMD -MP -O2 -mmcu=${CPU} -g
LCDLIB=lcd
LCDLIBOBJS=lcd.o
AVRDUDE=avrdude
AVDFLAGS=-p m324pa -P usb -c avrispmkII -F -B 10
OBJCOPY=avr-objcopy
OBJCFLAGS=-O ihex -R .eeprom -R .fuse -R .lock
CC=avr-gcc
LIBS=-L. -llcd
#LDFLAGS=-Wl,-u,vfprintf -lprintf_min


.PHONY: program clean

program: ${T}.hex
	${AVRDUDE} ${AVDFLAGS} -U flash:w:${T}.hex

${T}.hex: ${T}
	${OBJCOPY} ${OBJCFLAGS} ${T} ${T}.hex

${T}: ${OBJS}
	${CC} -mmcu=${CPU} -o ${T} ${LDFLAGS} ${OBJS} ${LIBS}

clean:
	rm -f *.o *.d *.hex
