#ifndef ADDRESSING_MODE
#define ADDRESSING_MODE

#include <stdint.h>

#include "Processor6502.h"

uint16_t resolve_acc(Processor6502* cpu);
uint16_t resolve_ime(Processor6502* cpu);
uint16_t resolve_r(Processor6502* cpu);
uint16_t resolve_imp(Processor6502* cpu);
uint16_t resolve_z(Processor6502* cpu);
uint16_t resolve_zx(Processor6502* cpu);
uint16_t resolve_zy(Processor6502* cpu);
uint16_t resolve_a(Processor6502* cpu);
uint16_t resolve_ax(Processor6502* cpu);
uint16_t resolve_ay(Processor6502* cpu);
uint16_t resolve_i(Processor6502* cpu);
uint16_t resolve_ix(Processor6502* cpu);
uint16_t resolve_iy(Processor6502* cpu);

#endif
