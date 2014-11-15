#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Processor6502.h"
#include "StatusRegister6502.h"

Processor6502* constructCPU(Processor6502* self, Memory16* memory)
{
	if (memory == NULL)
		return NULL;

	self->accumulator = 0;
	self->x = 0;
	self->y = 0;
	self->pc = 0;
	self->sp = 0xFF;

	self->status = NULL;
	constructStatus(&self->status);

	self->memory = memory;

	return self;
}

Processor6502* destructCPU(Processor6502* self)
{
	destructStatus(&self->status);
	destructMemory(&self->memory);

	return NULL;
}

void dumpCPU(Processor6502* self, FILE* output)
{
	fprintf(output, "ACC: %X\n", self->accumulator);
	fprintf(output, "  X: %X\n", self->x);
	fprintf(output, "  Y: %X\n", self->y);
	fprintf(output, " PC: %X\n", self->pc);
	fprintf(output, " SP: %X\n", 0x100 | self->sp);

	uint8_t n = isNegative(self->status)? 1 : 0;
	uint8_t v = overflowing(self->status)? 1 : 0;
	uint8_t b = breaking(self->status)? 1 : 0;
	uint8_t d = inDecimalMode(self->status)? 1 : 0;
	uint8_t i = isIRQdisabled(self->status)? 1 : 0;
	uint8_t z = isZero(self->status)? 1 : 0;
	uint8_t c = isCarrying(self->status)? 1 : 0;

	fprintf(output, "%d%d-%d%d%d%d%d\n", n, v, b, d, i, z, c);
	fprintf(output, "NV-BDIZC\n");
}