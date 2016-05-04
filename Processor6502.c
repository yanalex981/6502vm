#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Processor6502.h"
#include "StatusRegister6502.h"

Processor6502 *mkCPU(Memory16 *memory)
{
	if (memory == NULL)
		return NULL;

	Processor6502 *cpu = (Processor6502 *)malloc(sizeof(Processor6502));

	cpu->accumulator = 0;
	cpu->x = 0;
	cpu->y = 0;
	cpu->pc = 0;
	cpu->sp = 0xFF;

	cpu->status = mkStatus();

	cpu->memory = memory;

	return cpu;
}

void delCPU(Processor6502 **self)
{
	delStatus(&((*self)->status));
	delMemory(&((*self)->memory));

	*self = NULL;
}

void dumpCPU(Processor6502 *self, FILE *output)
{
	fprintf(output, "ACC: 0x%X\n", self->accumulator);
	fprintf(output, "  X: 0x%X\n", self->x);
	fprintf(output, "  Y: 0x%X\n", self->y);
	fprintf(output, " PC: 0x%X\n", self->pc);
	fprintf(output, " SP: 0x%X\n", 0x100 | self->sp);

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