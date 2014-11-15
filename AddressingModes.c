#include "AddressingModes.h"
#include "Memory16.h"
#include "Processor6502.h"

/* accumulator */
uint16_t resolve_acc(Processor6502* cpu)
{
	return cpu->pc;
}

/* immediate */
uint16_t resolve_ime(Processor6502* cpu)
{
	return ++cpu->pc;
}

/* relative */
uint16_t resolve_r(Processor6502* cpu)
{
	uint16_t address = ++cpu->pc;
	address += getByteAt(cpu->memory, cpu->pc);

	return address;
}

/* implied */
uint16_t resolve_imp(Processor6502* cpu)
{
	return cpu->pc;
}

/* zero page */
uint16_t resolve_z(Processor6502* cpu)
{
	return getByteAt(cpu->memory, ++cpu->pc);
}

/* zero page x index */
uint16_t resolve_zx(Processor6502* cpu)
{
	return resolve_z(cpu) + cpu->x;
}

/* zero page y index */
uint16_t resolve_zy(Processor6502* cpu)
{
	return resolve_z(cpu) + cpu->y;
}

/* absolute */
uint16_t resolve_a(Processor6502* cpu)
{
	uint16_t address = getLEWordAt(cpu->memory, ++cpu->pc);
	// printf("PC: %X a: %X\n", cpu->pc - 1, address);
	++cpu->pc;

	return address;
}

/* absolute x index */
uint16_t resolve_ax(Processor6502* cpu)
{
	return resolve_a(cpu) + cpu->x;
}

/* absolute y index */
uint16_t resolve_ay(Processor6502* cpu)
{
	return resolve_a(cpu) + cpu->y;
}

/* indirect */
uint16_t resolve_i(Processor6502* cpu)
{
	uint16_t address1 = getLEWordAt(cpu->memory, ++cpu->pc);
	++cpu->pc;

	uint16_t address2 = getLEWordAt(cpu->memory, address1);

	return address2;
}

/* indexed indirect (x) */
uint16_t resolve_ix(Processor6502* cpu)
{
	uint16_t address1 = getByteAt(cpu->memory, ++cpu->pc) + cpu->x;
	++cpu->pc;

	uint16_t address2 = getLEWordAt(cpu->memory, address1);

	return address2;
}

/* indirect indexed (y) */
uint16_t resolve_iy(Processor6502* cpu)
{
	uint16_t address = getLEWordAt(cpu->memory, ++cpu->pc) + cpu->y;
	++cpu->pc;

	return address;
}