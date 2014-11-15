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
void f()
{
	return;
}
// int main()
// {
// 	Memory16* memory = NULL;
// 	constructMemory(&memory, 0xFFFF);

// 	Processor6502* cpu = NULL;
// 	constructCPU(cpu, memory);

// 	while (!breaking(cpu->status))
// 	{
// 		uint8_t opcode = getByteAt(memory, cpu->pc);

// 		decode d = getDecoder(opcode);
// 		uint16_t decodedAddress = d(cpu);

// 		operate f = getInstruction(opcode);
// 		f(cpu, decodedAddress);

// 		++cpu->pc;
// 	}

// 	dumpCPU(cpu, stdout);

// 	return 0;
// }