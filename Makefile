CFLAGS = -Wall -Iinclude/ -std=c99

AddressingModes.o:	AddressingModes.h AddressingModes.c
Decoder.o:	Decoder.h Decoder.c
Instructions.o:	Instructions.h Instructions.c
Memory16.o:	Memory16.h Memory16.c
Processor6502.o:	Processor6502.h Processor6502.c
StatusRegister6502.o:	StatusRegister6502.h StatusRegister6502.c

machine:	AddressingModes.o Decoder.o Instructions.o Memory16.o Processor6502.o StatusRegister6502.o

clean:
	rm *.o *.exe