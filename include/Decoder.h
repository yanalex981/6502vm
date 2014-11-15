#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

#include "AddressingModes.h"
#include "Instructions.h"

typedef uint16_t (*decode)(Processor6502*);
typedef void (*operate)(Processor6502*, uint16_t);

// uint16_t (*getDecoder(uint8_t opcode))(Processor6502*);
// void (*getInstruction(uint8_t opcode))(Processor6502*, uint16_t);
decode getDecoder(uint8_t opcode);
operate getInstruction(uint8_t opcode);

#endif