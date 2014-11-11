#include "Instructions.h"
#include "Memory16.h"

/* LOAD & STORE */
void lda(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator = getByteAt(cpu->memory, address);

	// set zero flag
	// set negative flag
}

void ldx(Processor6502* cpu, uint16_t address)
{
	cpu->x = getByteAt(cpu->memory, address);

	// set zero flag
	// set negative flag
}

void ldy(Processor6502* cpu, uint16_t address)
{
	cpu->y = getByteAt(cpu->memory, address);

	// set zero flag
	// set negative flag
}

void sta(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, address, cpu->a);
}

void stx(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, address, cpu->x);
}

void sty(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, address, cpu->y);
}


/* Register Transfer */
void tax(Processor6502* cpu, uint16_t address)
{
	cpu->x = cpu->a;

	// set zero flag
	// set negative flag
}

void tay(Processor6502* cpu, uint16_t address)
{
	cpu->y = cpu->a;

	// set zero flag
	// set negative flag
}

void txa(Processor6502* cpu, uint16_t address)
{
	cpu->a = cpu->x;

	// set zero flag
	// set negative flag
}

void tya(Processor6502* cpu, uint16_t address)
{
	cpu->a = cpu->y;

	// set zero flag
	// set negative flag
}


/* Stack ALL IMPLIED */
void tsx(Processor6502* cpu, uint16_t address)
{
	cpu->x = cpu->sp;

	// set zero flag
	// set negative flag
}

void txs(Processor6502* cpu, uint16_t address)
{
	cpu->sp = cpu->x;
}

void pha(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, 0x100 | cpu->sp, cpu->a);
	--(cpu->sp);
}

void php(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, 0x100 | cpu->sp, cpu->a);
	--(cpu->sp);
}

void pla(Processor6502* cpu, uint16_t address)
{
	++(cpu->sp);
	cpu->accumulator = getByteAt(cpu->memory, 0x100 | cpu->sp);

	// set zero flag
	// set negative flag
}

void plp(Processor6502* cpu, uint16_t address)
{
	++(cpu->sp);
	cpu->status = getByteAt(cpu->memory, 0x100 | cpu->sp);
	// set all flags
}


/* Logical */
void and(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator & operand;
	// set zero flag
	// set negative flag
}

void eor(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator ^ operand;

	// set zero flag
	// set negative flag
}

void ora(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator | operand;

	// set zero flag
	// set negative flag
}

/* FIGURE OUT THIS ONE */
void bit(Processor6502* cpu, uint16_t address)
{
	uint8_t result = cpu->accumulator & getByteAt(cpu->memory, address);
	// set zero flag
	// set overflow flag
	// set negative flag
}


/* Arithmetic */
void adc(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator += getByteAt(cpu->memory, address) + (cpu->status >> 7);

	// set carry flag
	// set zero flag
	// set overflow flag
	// set negative flag
}

void sbc(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator = cpu->accumulator - getByteAt(cpu->memory, address) - (cpu->status >> 7);

	// set carry flag
	// set zero flag
	// set overflow flag
	// set negative flag
}

void cmp(Processor6502* cpu, uint16_t address)
{
	uint8_t result = cpu->accumulator - getByteAt(cpu->memory, address);

	// set carry flag
	// set zero flag
	// set negative flag
}

void cpx(Processor6502* cpu, uint16_t address)
{
	uint8_t result = cpu->x - getByteAt(cpu->memory, address);

	// set carry flag
	// set zero flag
	// set negative flag	
}

void cpy(Processor6502* cpu, uint16_t address)
{
	uint8_t result = cpu->y - getByteAt(cpu->memory, address);

	// set carry flag
	// set zero flag
	// set negative flag
}


/* Increment & Decrement */
void inc(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	setByteAt(cpu->memory, address, ++byte);

	// set zero flag
	// set negative flag
}

void inx(Processor6502* cpu, uint16_t address)
{
	++(cpu->x);

	// set zero flag
	// set negative flag
}

void iny(Processor6502* cpu, uint16_t address)
{
	++(cpu->y);

	// set zero flag
	// set negative flag
}

void dec(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	setByteAt(cpu->memory, address, ++byte);

	// set zero flag
	// set negative flag
}

void dex(Processor6502* cpu, uint16_t address)
{
	--(cpu->x);

	// set zero flag
	// set negative flag
}

void dey(Processor6502* cpu, uint16_t address)
{
	--(cpu->y);

	// set zero flag
	// set negative flag
}


/* Shift */
uint8_t lShift(uint8_t byte, uint8_t* status)
{
	*status = byte >> 7;
	return byte << 1;
}

uint8_t rShift(uint8_t byte, uint8_t* status)
{
	*status = 0x01 & byte;
	return byte >> 1;
}

/*
********
store b7
left shift
set b0 to carry
set carry to b7

temp = byte >> 7
result = byte << 1

*/
uint8_t rotateL(uint8_t byte, uint8_t* status)
{
	uint8_t temp = byte >> 7;
	uint8_t result = byte << 1;
	result = (result & ~0x01) | (*status & ~0x01);
	*status = (*status & ~0x01) | temp;

	return result;
}

uint8_t rotateR(uint8_t byte, uint8_t* status)
{
	uint8_t temp = byte & 0x01;
	uint8_t result = byte >> 1;
	result = (result & ~0x80) | (*status << 7);
	*status = (*status & ~0x01) | temp;

	return result;
}

void aslA(Processor6502* cpu, uint16_t operand)
{
	//
}

void lsrA(Processor6502* cpu, uint16_t operand)
{
	//
}

void rolA(Processor6502* cpu, uint16_t operand)
{
	//
}

void rorA(Processor6502* cpu, uint16_t operand)
{
	//
}

void asl(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator <<= 1;

	// set carry flag
	// set zero flag
	// set negative flag
}

void lsr(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator >>= 1;

	// set carry flag
	// set zero flag
	// set negative flag
}

void rol(Processor6502* cpu, uint16_t address)
{
	uint16_t byte = getByteAt(cpu->memory, address) << 1;
	byte |= (byte >> 8);


	// set carry flag
	// set zero flag
	// set negative flag
}

void ror(Processor6502* cpu, uint16_t address)
{

	// set carry flag
	// set zero flag
	// set negative flag
}

void aslA(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator <<= 1;

	// set carry flag
	// set zero flag
	// set negative flag
}

void lsrA(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator >>= 1;

	// set carry flag
	// set zero flag
	// set negative flag
}

void rolA(Processor6502* cpu, uint16_t address)
{
	uint16_t byte = getByteAt(cpu->memory, address) << 1;
	byte |= (byte >> 8);


	// set carry flag
	// set zero flag
	// set negative flag
}

void rorA(Processor6502* cpu, uint16_t address)
{

	// set carry flag
	// set zero flag
	// set negative flag
}


/* Jump and Call */
void jmp(Processor6502* cpu, uint16_t address)
{

}

void jsr(Processor6502* cpu, uint16_t address)
{

}

void rts(Processor6502* cpu, uint16_t address)
{

}


/* Branch */
void bcc(Processor6502* cpu, uint16_t address)
{

}

void bcs(Processor6502* cpu, uint16_t address)
{

}

void beq(Processor6502* cpu, uint16_t address)
{

}

void bmi(Processor6502* cpu, uint16_t address)
{

}

void bne(Processor6502* cpu, uint16_t address)
{

}

void bpl(Processor6502* cpu, uint16_t address)
{

}

void bvc(Processor6502* cpu, uint16_t address)
{

}

void bvs(Processor6502* cpu, uint16_t address)
{

}


/* Status Flag */
void clc(Processor6502* cpu, uint16_t address)
{

}

void cld(Processor6502* cpu, uint16_t address)
{

}

void cli(Processor6502* cpu, uint16_t address)
{

}

void clv(Processor6502* cpu, uint16_t address)
{

}

void sec(Processor6502* cpu, uint16_t address)
{

}

void sed(Processor6502* cpu, uint16_t address)
{

}

void sei(Processor6502* cpu, uint16_t address)
{

}


/* System */
void brk(Processor6502* cpu, uint16_t address)
{
	// set break flag
}

void nop(Processor6502* cpu, uint16_t address)
{

}

void rti(Processor6502* cpu, uint16_t address)
{
	// set all flags
}
