PRG            = rotenc
OBJ            = rotenc.c
LIBNAME	       = rotenc
PROGRAMMER     = usbasp
PORT           = usb
MCU_TARGET     = attiny85 
AVRDUDE_TARGET = attiny85
OPTIMIZE       = -Os
DEFS           = 
LIBS           =

HZ          = 8000000
#
# NOTE - This is specifically for compiling the library not for general compiles
#
# You should not have to change anything below here.

CC             = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -c -DF_CPU=$(HZ) -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
#override LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).o 

$(PRG).o: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	
library: 
	avr-ar rcs lib$(LIBNAME).a *.o
		
clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak *.hex *.bin *.srec
	rm -rf *.lst *.map *.a 


