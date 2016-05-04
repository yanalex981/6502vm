#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Decoder.h"
#include "Processor6502.h"
#include "StatusRegister6502.h"

// tags used for debugging purposes
char tags[][4] =
{
	"BRK", "ORA", "NULL", "NULL", "NULL", "ORA", "ASL", "NULL", "PHP", "ORA", "ASL", "NULL", "NULL", "ORA", "ASL", "NULL",
	"BPL", "ORA", "NULL", "NULL", "NULL", "ORA", "ASL", "NULL", "CLC", "ORA", "NULL", "NULL", "NULL", "ORA", "ASL", "NULL",
	"JSR", "AND", "NULL", "NULL", "BIT", "AND", "ROL", "NULL", "PLP", "AND", "ROL", "NULL", "BIT", "AND", "ROL", "NULL",
	"BMI", "AND", "NULL", "NULL", "NULL", "AND", "ROL", "NULL", "SEC", "AND", "NULL", "NULL", "NULL", "AND", "ROL", "NULL",
	"RTI", "EOR", "NULL", "NULL", "NULL", "EOR", "LSR", "NULL", "PHA", "EOR", "LSR", "NULL", "JMP", "EOR", "LSR", "NULL",
	"BVC", "EOR", "NULL", "NULL", "NULL", "EOR", "LSR", "NULL", "CLI", "EOR", "NULL", "NULL", "NULL", "EOR", "LSR", "NULL",
	"RTS", "ADC", "NULL", "NULL", "NULL", "ADC", "ROR", "NULL", "PLA", "ADC", "ROR", "NULL", "JMP", "ADC", "ROR", "NULL",
	"BVS", "ADC", "NULL", "NULL", "NULL", "ADC", "ROR", "NULL", "SEI", "ADC", "NULL", "NULL", "NULL", "ADC", "ROR", "NULL",
	"NULL", "STA", "NULL", "NULL", "STY", "STA", "STX", "NULL", "DEY", "NULL", "TXA", "NULL", "STY", "STA", "STX", "NULL",
	"BCC", "STA", "NULL", "NULL", "STY", "STA", "STX", "NULL", "TYA", "STA", "TXS", "NULL", "NULL", "STA", "NULL", "NULL",
	"LDY", "LDA", "LDX", "NULL", "LDY", "LDA", "LDX", "NULL", "TAY", "LDA", "TAX", "NULL", "LDY", "LDA", "LDX", "NULL",
	"BCS", "LDA", "NULL", "NULL", "LDY", "LDA", "LDX", "NULL", "CLV", "LDA", "TSX", "NULL", "LDY", "LDA", "LDX", "NULL",
	"CPY", "CMP", "NULL", "NULL", "CPY", "CMP", "DEC", "NULL", "INY", "CMP", "DEX", "NULL", "CPY", "CMP", "DEC", "NULL",
	"BNE", "CMP", "NULL", "NULL", "NULL", "CMP", "DEC", "NULL", "CLD", "CMP", "NULL", "NULL", "NULL", "CMP", "DEC", "NULL",
	"CPX", "SBC", "NULL", "NULL", "CPX", "SBC", "INC", "NULL", "INX", "SBC", "NOP", "NULL", "CPX", "SBC", "INC", "NULL",
	"BEQ", "SBC", "NULL", "NULL", "NULL", "SBC", "INC", "NULL", "SED", "SBC", "NULL", "NULL", "NULL", "SBC", "INC", "NULL"
};

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

void run(Processor6502 *self)
{
	while (!breaking(self->status))
	{
		uint8_t opcode = getByteAt(self->memory, self->pc);
		// using my tags for debugging purposes
		printf("PC: %X\topcode: %X %s\tStatus: %X\n", self->pc, opcode, tags[opcode], getStatusByte(self->status));

		decode d = getDecoder(opcode);

		if (d == NULL)
		{
			printf("Cannot decode instruction at: %X. Opcode: %X\n", self->pc, opcode);
			d = resolve_acc;
		}

		uint16_t decodedAddress = d(self);

		operate f = getInstruction(opcode);

		if (f == NULL)
		{
			printf("Illegal instruction encountered at: %X. Opcode: %X\n", self->pc, opcode);
			f = brk;
		}

		f(self, decodedAddress);

		++self->pc;
	}
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