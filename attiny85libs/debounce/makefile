PRG            = debounce
OBJ            = debounce.S
LIBNAME		   = debounce
PROGRAMMER     = usbasp
PORT           = usb
MCU_TARGET     = attiny85 
AVRDUDE_TARGET = attiny85
OPTIMIZE       = -Os
LD			   = /home/spb/avrsource/attiny85libs/
#DEFS           = -I$(LD)serial85dbg -I$(LD)my85libs -I$(LD)usi 
#DEFS2	       = -L$(LD)serial85dbg -L$(LD)my85libs -L$(LD)usi
#LIBS           = -l85dbg -lusi -lmy85

HZ          = 8000000

# You should not have to change anything below here.

CC             = avr-gcc

# Override is only needed by avr-lib build system.

override ASFLAGS       = -mmcu=$(MCU_TARGET) -c -Wa,-adhlns=$(<:.S=.lst)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).o 

$(PRG).o: $(OBJ)
	$(CC) $(ASFLAGS) -o $@ $^ $(LIBS)
	
library: 
	avr-ar rcs lib$(LIBNAME).a *.o
		
clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak *.hex *.bin *.srec
	rm -rf *.lst *.map *.a 

