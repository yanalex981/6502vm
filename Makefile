INC = ./include/
OBJ = ./objects/
CFLAGS = -g -Wall -I$(INC) -std=c99

Machine:	Machine.o AddressingModes.o Decoder.o Instructions.o Memory16.o Processor6502.o StatusRegister6502.o
Machine.o:	Machine.c
AddressingModes.o:	AddressingModes.c
Decoder.o:	Decoder.c
Instructions.o:	Instructions.c
Memory16.o:	Memory16.c
Processor6502.o:	Processor6502.c
StatusRegister6502.o:	StatusRegister6502.c

.PHONY: clean
clean:
	-rm *.o *.exe Machine