#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <stdint.h>

#include "Processor6502.h"

/*
accumulator		acc
immediate			imm
zero page			z
zero page x			zx
zero page y			xy
absolute			a
absolute x			ax
absolute y			ay
relative			r
implicit			imp
indirect			ind
indexed indirect x	idx
indirected index y	idy
*/

/* LOAD & STORE */
void lda(Processor6502* cpu, uint16_t operand);
void ldx(Processor6502* cpu, uint16_t operand);
void ldy(Processor6502* cpu, uint16_t operand);
void sta(Processor6502* cpu, uint16_t operand);
void stx(Processor6502* cpu, uint16_t operand);
void sty(Processor6502* cpu, uint16_t operand);

/* Register Transfer */
void tax(Processor6502* cpu, uint16_t operand);
void tay(Processor6502* cpu, uint16_t operand);
void txa(Processor6502* cpu, uint16_t operand);
void tya(Processor6502* cpu, uint16_t operand);

/* Stack ALL IMPLIED */
void tsx(Processor6502* cpu, uint16_t operand);
void txs(Processor6502* cpu, uint16_t operand);
void pha(Processor6502* cpu, uint16_t operand);
void php(Processor6502* cpu, uint16_t operand);
void pla(Processor6502* cpu, uint16_t operand);
void plp(Processor6502* cpu, uint16_t operand);

/* Logical */
void and(Processor6502* cpu, uint16_t operand);
void eor(Processor6502* cpu, uint16_t operand);
void ora(Processor6502* cpu, uint16_t operand);
void bit(Processor6502* cpu, uint16_t operand);

/* Arithmetic */
void adc(Processor6502* cpu, uint16_t operand);
void sbc(Processor6502* cpu, uint16_t operand);
void cmp(Processor6502* cpu, uint16_t operand);
void cpx(Processor6502* cpu, uint16_t operand);
void cpy(Processor6502* cpu, uint16_t operand);

/* Increment & Decrement */
void inc(Processor6502* cpu, uint16_t operand);
void inx(Processor6502* cpu, uint16_t operand);
void iny(Processor6502* cpu, uint16_t operand);
void dec(Processor6502* cpu, uint16_t operand);
void dex(Processor6502* cpu, uint16_t operand);
void dey(Processor6502* cpu, uint16_t operand);

/* Shift */
void aslA(Processor6502* cpu, uint16_t operand);
void lsrA(Processor6502* cpu, uint16_t operand);
void rolA(Processor6502* cpu, uint16_t operand);
void rorA(Processor6502* cpu, uint16_t operand);

void asl(Processor6502* cpu, uint16_t operand);
void lsr(Processor6502* cpu, uint16_t operand);
void rol(Processor6502* cpu, uint16_t operand);
void ror(Processor6502* cpu, uint16_t operand);

/* Jump and Call */
void jmp(Processor6502* cpu, uint16_t operand);
void jsr(Processor6502* cpu, uint16_t operand);
void rts(Processor6502* cpu, uint16_t operand);

/* Branch */
void bcc(Processor6502* cpu, uint16_t operand);
void bcs(Processor6502* cpu, uint16_t operand);
void beq(Processor6502* cpu, uint16_t operand);
void bmi(Processor6502* cpu, uint16_t operand);
void bne(Processor6502* cpu, uint16_t operand);
void bpl(Processor6502* cpu, uint16_t operand);
void bvc(Processor6502* cpu, uint16_t operand);
void bvs(Processor6502* cpu, uint16_t operand);

/* Status Flag */
void clc(Processor6502* cpu, uint16_t operand);
void cld(Processor6502* cpu, uint16_t operand);
void cli(Processor6502* cpu, uint16_t operand);
void clv(Processor6502* cpu, uint16_t operand);
void sec(Processor6502* cpu, uint16_t operand);
void sed(Processor6502* cpu, uint16_t operand);
void sei(Processor6502* cpu, uint16_t operand);

/* System */
void brk(Processor6502* cpu, uint16_t operand);
void nop(Processor6502* cpu, uint16_t operand);
void rti(Processor6502* cpu, uint16_t operand);

#endif
