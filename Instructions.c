#include "Instructions.h"
#include "Memory16.h"
#include "StatusRegister6502.h"
#include "Processor6502.h"

// TODO: USE A STACK POINTER STRUCT TO SAFELY
//       EMULATE THE LEADING 1 IN THE STACK ADDRESS
//       AKA PREVENT ORING cpu->sp BY 0x100

// NOTE: PC INCREMENTS BEFORE FETCH

void checkZeroNegative(uint8_t byte, StatusRegister6502* status)
{
	if (byte == 0)
		setZero(status);
	else
		clearZero(status);

	if (byte >> 7 == 1)
		setNegative(status);
	else
		clearNegative(status);
}

// NOTE: TWO'S COMPLEMENT
//    a - b
//  = a + (~b + 1)
void checkCarry(uint8_t a, uint8_t b, StatusRegister6502* status)
{
	uint16_t result = a + b;

	if (((result >> 8) & 1) == 1)
		setCarry(status);
	else
		clearCarry(status);
}

void checkOverflow(uint8_t a, uint8_t b, StatusRegister6502* status)
{
	uint16_t result = a + b;

	if (result >= 0x80)
		setOverflow(status);
	else
		clearOverflow(status);
}

/* LOAD & STORE */
void lda(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator = getByteAt(cpu->memory, address);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void ldx(Processor6502* cpu, uint16_t address)
{
	cpu->x = getByteAt(cpu->memory, address);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void ldy(Processor6502* cpu, uint16_t address)
{
	cpu->y = getByteAt(cpu->memory, address);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void sta(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, address, cpu->accumulator);
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
	cpu->x = cpu->accumulator;

	checkZeroNegative(cpu->x, cpu->status);
}

void tay(Processor6502* cpu, uint16_t address)
{
	cpu->y = cpu->accumulator;

	checkZeroNegative(cpu->y, cpu->status);
}

void txa(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator = cpu->x;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void tya(Processor6502* cpu, uint16_t address)
{
	cpu->accumulator = cpu->y;

	checkZeroNegative(cpu->accumulator, cpu->status);
}


/* Stack ALL IMPLIED */
void tsx(Processor6502* cpu, uint16_t address)
{
	cpu->x = cpu->sp;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void txs(Processor6502* cpu, uint16_t address)
{
	cpu->sp = cpu->x;
}

void pha(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, 0x100 | cpu->sp, cpu->accumulator);
	--(cpu->sp);
}

void php(Processor6502* cpu, uint16_t address)
{
	setByteAt(cpu->memory, 0x100 | cpu->sp, getStatusByte(cpu->status));
	--(cpu->sp);
}

void pla(Processor6502* cpu, uint16_t address)
{
	++(cpu->sp);
	cpu->accumulator = getByteAt(cpu->memory, 0x100 | cpu->sp);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void plp(Processor6502* cpu, uint16_t address)
{
	++(cpu->sp);
	setStatusByte(cpu->status, getByteAt(cpu->memory, 0x100 | cpu->sp));
}


/* Logical */
void and(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator & operand;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void eor(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator ^ operand;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void ora(Processor6502* cpu, uint16_t address)
{
	uint8_t operand = getByteAt(cpu->memory, address);
	cpu->accumulator = cpu->accumulator | operand;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

/* TODO: FIGURE OUT THIS ONE */
void bit(Processor6502* cpu, uint16_t address)
{
	uint8_t result = cpu->accumulator & getByteAt(cpu->memory, address);
	
	checkZeroNegative(result, cpu->status);

	if (((result >> 6) & 1) == 1)
		setOverflow(cpu->status);
	else
		clearOverflow(cpu->status);
}


/* Arithmetic */
void adc(Processor6502* cpu, uint16_t address)
{
	uint8_t a = cpu->accumulator;
	uint8_t b = getByteAt(cpu->memory, address);

	checkCarry(a, b, cpu->status);
	checkOverflow(a, b, cpu->status);

	cpu->accumulator = a + b;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void sbc(Processor6502* cpu, uint16_t address)
{
	uint8_t a = cpu->accumulator;
	uint8_t b = ~(getByteAt(cpu->memory, address)) + 1;

	checkCarry(a, b, cpu->status);
	checkOverflow(a, b, cpu->status);

	cpu->accumulator = a + b;

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void setCompareFlags(uint8_t a, uint8_t b, StatusRegister6502* status)
{
	if (a >= b)
		setCarry(status);
	else
		clearCarry(status);

	if (a == b)
		setZero(status);
	else
		clearCarry(status);

	if (a < b)
		setNegative(status);
	else
		clearCarry(status);
}

void cmp(Processor6502* cpu, uint16_t address)
{
	uint8_t a = cpu->accumulator;
	uint8_t b = getByteAt(cpu->memory, address);

	setCompareFlags(a, b, cpu->status);
}

void cpx(Processor6502* cpu, uint16_t address)
{
	uint8_t a = cpu->x;
	uint8_t b = getByteAt(cpu->memory, address);

	setCompareFlags(a, b, cpu->status);
}

void cpy(Processor6502* cpu, uint16_t address)
{
	uint8_t a = cpu->y;
	uint8_t b = getByteAt(cpu->memory, address);

	setCompareFlags(a, b, cpu->status);
}


/* Increment & Decrement */
void inc(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	setByteAt(cpu->memory, address, ++byte);

	checkZeroNegative(byte, cpu->status);
}

void inx(Processor6502* cpu, uint16_t address)
{
	++(cpu->x);

	checkZeroNegative(cpu->x, cpu->status);
}

void iny(Processor6502* cpu, uint16_t address)
{
	++(cpu->y);

	checkZeroNegative(cpu->y, cpu->status);
}

void dec(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	setByteAt(cpu->memory, address, --byte);

	checkZeroNegative(byte, cpu->status);
}

void dex(Processor6502* cpu, uint16_t address)
{
	--(cpu->x);

	checkZeroNegative(cpu->x, cpu->status);
}

void dey(Processor6502* cpu, uint16_t address)
{
	--(cpu->y);

	checkZeroNegative(cpu->y, cpu->status);
}


/* Shift */
// TODO: MAJOR REFACTORING CONSIDERED
// TODO: REWRITE IMPLEMENTATION such that
//       carry is set if byte > 7F
//       makes code more readable and maintainable
// TODO: consider using more register structs
//       and functions rather than plain primitive
//       values to improve reusability
uint8_t lShift(uint8_t byte, StatusRegister6502* status)
{
	if (byte >= 0x80)
		setCarry(status);
	else
		clearCarry(status);

	return byte << 1;
}

uint8_t rShift(uint8_t byte, StatusRegister6502* status)
{
	if (byte % 1 == 1)
		setCarry(status);
	else
		clearCarry(status);

	return byte >> 1;
}

uint8_t rotateL(uint8_t byte, StatusRegister6502* status)
{
	bool carry = byte >= 0x80;
	uint8_t shifted = byte << 1;

	if (isCarrying(status))
		shifted |= 1;

	if (carry)
		setCarry(status);
	else
		clearCarry(status);

	return shifted;
}

uint8_t rotateR(uint8_t byte, StatusRegister6502* status)
{
	bool carry = ((byte & 1) == 1);
	uint8_t shifted = byte >> 1;

	if (isCarrying(status))
		shifted |= 1 << 7;

	if (carry)
		setCarry(status);
	else
		clearCarry(status);

	return shifted;
}

void aslA(Processor6502* cpu, uint16_t operand)
{
	cpu->accumulator = lShift(cpu->accumulator, cpu->status);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void lsrA(Processor6502* cpu, uint16_t operand)
{
	cpu->accumulator = rShift(cpu->accumulator, cpu->status);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void rolA(Processor6502* cpu, uint16_t operand)
{
	cpu->accumulator = rotateL(cpu->accumulator, cpu->status);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void rorA(Processor6502* cpu, uint16_t operand)
{
	cpu->accumulator = rotateR(cpu->accumulator, cpu->status);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void asl(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	byte = lShift(byte, cpu->status);
	setByteAt(cpu->memory, address, byte);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void lsr(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	byte = rShift(byte, cpu->status);
	setByteAt(cpu->memory, address, byte);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void rol(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	byte = rotateL(byte, cpu->status);
	setByteAt(cpu->memory, address, byte);

	checkZeroNegative(cpu->accumulator, cpu->status);
}

void ror(Processor6502* cpu, uint16_t address)
{
	uint8_t byte = getByteAt(cpu->memory, address);
	byte = rotateR(byte, cpu->status);
	setByteAt(cpu->memory, address, byte);

	checkZeroNegative(cpu->accumulator, cpu->status);
}


/* Jump and Call */
void jmp(Processor6502* cpu, uint16_t address)
{
	cpu->pc = getByteAt(cpu->memory, address) - 1;
}

void jsr(Processor6502* cpu, uint16_t address)
{
	setLEWordAt(cpu->memory, cpu->sp, address + 2);
	--(cpu->sp);
	cpu->pc = address - 1;
}

void rts(Processor6502* cpu, uint16_t address)
{
	cpu->pc = getBEWordAt(cpu->memory, cpu->sp);
	++(cpu->sp);
}


/* Branch */
void bcc(Processor6502* cpu, uint16_t address)
{
	if (!isCarrying(cpu->status))
		cpu->pc = address - 1;
}

void bcs(Processor6502* cpu, uint16_t address)
{
	if (isCarrying(cpu->status))
		cpu->pc = address - 1;
}

void bne(Processor6502* cpu, uint16_t address)
{
	if (!isZero(cpu->status))
		cpu->pc = address - 1;
}

void beq(Processor6502* cpu, uint16_t address)
{
	if (isZero(cpu->status))
		cpu->pc = address - 1;
}

void bpl(Processor6502* cpu, uint16_t address)
{
	if (!isNegative(cpu->status))
		cpu->pc = address - 1;
}

void bmi(Processor6502* cpu, uint16_t address)
{
	if (isNegative(cpu->status))
		cpu->pc = address - 1;
}

void bvc(Processor6502* cpu, uint16_t address)
{
	if (!overflowing(cpu->status))
		cpu->pc = address - 1;
}

void bvs(Processor6502* cpu, uint16_t address)
{
	if (overflowing(cpu->status))
		cpu->pc = address - 1;
}


/* Status Flag */
void clc(Processor6502* cpu, uint16_t address)
{
	clearCarry(cpu->status);
}

void cld(Processor6502* cpu, uint16_t address)
{
	clearDecimalMode(cpu->status);
}

void cli(Processor6502* cpu, uint16_t address)
{
	clearIRQ(cpu->status);
}

void clv(Processor6502* cpu, uint16_t address)
{
	clearOverflow(cpu->status);
}

void sec(Processor6502* cpu, uint16_t address)
{
	setCarry(cpu->status);
}

void sed(Processor6502* cpu, uint16_t address)
{
	setDecimalMode(cpu->status);
}

void sei(Processor6502* cpu, uint16_t address)
{
	setIRQDisabled(cpu->status);
}


/* System */
void brk(Processor6502* cpu, uint16_t address)
{
	setBreak(cpu->status);
}

void nop(Processor6502* cpu, uint16_t address) {}

void rti(Processor6502* cpu, uint16_t address)
{
	--(cpu->sp);

	setStatusByte(cpu->status, getByteAt(cpu->memory, 0x100 | cpu->sp));
}