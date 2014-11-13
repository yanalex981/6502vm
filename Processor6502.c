#include <stdint.h>
#include <stdio.h>

#include "Processor6502.h"
#include "StatusRegister6502.h"

void dumpCPU(Processor6502* self, FILE* output)
{
	fprintf(output, "%u\n", self->accumulator);
	fprintf(output, "%u\n", self->x);
	fprintf(output, "%u\n", self->y);
	fprintf(output, "%u\n", self->pc);
	fprintf(output, "%u\n", self->sp);

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