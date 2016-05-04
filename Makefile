INC = ./include/
OBJ = ./objects/
CFLAGS = -g -Wall -I$(INC) -std=c11

6502vm: 6502vm.o AddressingModes.o Decoder.o Instructions.o Memory16.o Processor6502.o StatusRegister6502.o

.PHONY: clean
clean:
	rm *.o *.exe 6502vm