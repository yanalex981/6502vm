#ifndef PROCESSOR6502
#define PROCESSOR6502

#include <stdint.h>
#include <stdio.h>

#include "Memory16.h"
#include "StatusRegister6502.h"

typedef struct {
	uint8_t accumulator;
	uint8_t x;
	uint8_t y;
	uint16_t pc;
	uint8_t sp;
	StatusRegister6502* status;
	Memory16* memory;
} Processor6502;

Processor6502 *mkCPU(Memory16 *memory);
void delCPU(Processor6502 **self);

void dumpCPU(Processor6502* self, FILE* output);

#endif