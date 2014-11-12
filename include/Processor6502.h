#ifndef PROCESSOR6502
#define PROCESSOR6502

#include <stdint.h>
#include <stdio.h>

#include "Memory16.h"
#include "StatusRegister6502.h"

typedef struct Processor6502 {
	uint8_t accumulator;
	uint8_t x;
	uint8_t y;
	uint16_t pc;
	uint8_t sp;
	StatusRegister6502* status;
	Memory16* ram;
} Processor6502;

void dumpCPU(Processor6502* self, FILE* output);

#endif