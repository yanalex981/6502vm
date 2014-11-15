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
	get instruction function
execute
	call instruction function
increment pc
*/

int main()
{
	Memory16* memory = NULL;
	constructMemory(&memory, 0xFFFF);

	Processor6502* cpu = malloc(sizeof(Processor6502));
	constructCPU(cpu, memory);

	uint16_t i = 0;

	setByteAt(memory, i++, 0x4C);	// jmp
	setByteAt(memory, i++, 0x00);	// 00
	setByteAt(memory, i++, 0x06);	// 06

	i = 600;

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

		printf("PC: %X d: %p f: %p\n", cpu->pc, d, f);

		++cpu->pc;
	}

	dumpCPU(cpu, stdout);

	printf("Address %X: %X\n", 32, getByteAt(memory, 32));

	return 0;
}