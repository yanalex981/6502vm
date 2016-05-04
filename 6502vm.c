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

uint8_t *readBytesFrom(char *filename, size_t *size)
{
	FILE *file = fopen(filename, "rb");

	if (!file)
	{
		printf("%s not found\n", filename);

		exit(2);
	}

	fseek(file, 0, SEEK_END);
	*size = ftell(file);
	fseek(file, 0, 0);
	uint8_t *buffer = (uint8_t *)malloc(*size);
	fread(buffer, sizeof(uint8_t), *size, file);
	fclose(file);

	return buffer;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Bad arguments\n");

		exit(1);
	}

	char *filename = argv[1];
	size_t imgSize;
	uint8_t *image = readBytesFrom(filename, &imgSize);
	Memory16 *memory = mkMemoryFrom(image, imgSize, 0xFFFF);
	Processor6502 *cpu = mkCPU(memory);
	free(image);

	run(cpu);

	printf("\n");
	dumpCPU(cpu, stdout);

	return 0;
}