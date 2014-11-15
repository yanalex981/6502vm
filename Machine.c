#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "AddressingModes.h"
#include "Decoder.h"
#include "Instructions.h"
#include "Memory16.h"
#include "Processor6502.h"
#include "StatusRegister6502.h"

/*
while !cpu.status.break

fetch
	get instruction opcode
decode
	get decode function
	call decode function
		increment pc or branching won't work...
	pc should now be 1 before next opcode
	get instruction function
execute
	call instruction function
increment pc
pc points to next opcode
*/

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

int main()
{
	Memory16* memory = NULL;
	constructMemory(&memory, 0xFFFF);

	Processor6502* cpu = malloc(sizeof(Processor6502));
	constructCPU(cpu, memory);

	uint16_t i = 0;

	setByteAt(memory, i++, 0x4C);
	setByteAt(memory, i++, 0x00);
	setByteAt(memory, i++, 0x06);

	i = 0x600;

	setByteAt(memory, i++, 0xa9);
	setByteAt(memory, i++, 0x00);
	setByteAt(memory, i++, 0xa2);
	setByteAt(memory, i++, 0x00);
	setByteAt(memory, i++, 0xe0);
	setByteAt(memory, i++, 0x06);
	setByteAt(memory, i++, 0xf0);
	setByteAt(memory, i++, 0x08);
	setByteAt(memory, i++, 0x86);
	setByteAt(memory, i++, 0x32);
	setByteAt(memory, i++, 0xe5);
	setByteAt(memory, i++, 0x32);
	setByteAt(memory, i++, 0xe8);
	setByteAt(memory, i++, 0x4c);
	setByteAt(memory, i++, 0x04);
	setByteAt(memory, i++, 0x06);
	setByteAt(memory, i++, 0x00);

	while (!breaking(cpu->status))
	{
		uint8_t opcode = getByteAt(memory, cpu->pc);
		// using my tags for debugging purposes
		printf("PC: %X\topcode: %X %s\tStatus: %X\n", cpu->pc, opcode, tags[opcode], getStatusByte(cpu->status));

		decode d = getDecoder(opcode);

		if (d == NULL)
		{
			printf("Cannot decode instruction at: %X. Opcode: %X\n", cpu->pc, opcode);
			d = resolve_acc;
		}

		uint16_t decodedAddress = d(cpu);

		operate f = getInstruction(opcode);

		if (f == NULL)
		{
			printf("Illegal instruction encountered at: %X. Opcode: %X\n", cpu->pc, opcode);
			f = brk;
		}

		f(cpu, decodedAddress);

		++cpu->pc;
	}

	printf("\n");
	dumpCPU(cpu, stdout);

	return 0;
}