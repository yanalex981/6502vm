INC = ./include/
OBJ = ./objects/
CFLAGS = -g -Wall -I$(INC) -std=c11

Machine: Machine.o AddressingModes.o Decoder.o Instructions.o Memory16.o Processor6502.o StatusRegister6502.o

.PHONY: clean
clean:
	rm *.o *.exe Machine