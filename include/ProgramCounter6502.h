#ifndef PROGRAM_COUNTER_6502
#define PROGRAM_COUNTER_6502

#include <stdio.h>
#include <stdint.h>

typedef struct ProgramCounter6502
{
	uint16_t address;
	uint8_t* widths;
} ProgramCounter6502;

void next(ProgramCounter6502* self);
void readFrom(FILE* input, size_t* length, uint8_t** output);

#endif