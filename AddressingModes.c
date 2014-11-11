#include "AddressingModes.h"
#include "Memory16.h"

/* accumulator */
uint16_t resolve_acc(Processor6502* cpu)
{
	return cpu->pc;
}

/* immediate */
uint16_t resolve_ime(Processor6502* cpu)
{
	return cpu->pc + 1;
}

/* relative */
uint16_t resolve_r(Processor6502* cpu)
{
	return cpu->pc + getByteAt(cpu->memory, pc + 1);
}

/* implied */
uint16_t resolve_imp(Processor6502* cpu)
{
	return cpu->pc;
}

/* zero page */
uint16_t resolve_z(Processor6502* cpu)
{
	return getByteAt(cpu->pc + 1);
}

/* zero page x index */
uint16_t resolve_zx(Processor6502* cpu)
{
	return getByteAt(cpu->pc + 1) + cpu->x;
}

/* zero page y index */
uint16_t resolve_zy(Processor6502* cpu)
{
	return getByteAt(cpu->pc + 1) + cpu->y;
}

/* absolute */
uint16_t resolve_a(Processor6502* cpu)
{
	return getLEDWordAt(cpu->memory, cpu->pc + 1);
}

/* absolute x index */
uint16_t resolve_ax(Processor6502* cpu)
{
	return getLEDWordAt(cpu->memory, cpu->pc + 1) + cpu->x;
}

/* absolute y index */
uint16_t resolve_ay(Processor6502* cpu)
{
	return getLEDWordAt(cpu->memory, cpu->pc + 1) + cpu->y;
}

/* indirect */
uint16_t resolve_i(Processor6502* cpu)
{
	uint16_t address1 = getLEDWordAt(cpu->memory, cpu->pc + 1);
	uint16_t address2 = getLEDWordAt(cpu->memory, address1);

	return address2;
}

/* indexed indirect (x) */
uint16_t resolve_ix(Processor6502* cpu)
{
	uint16_t address1 = getByteAt(cpu->memory, cpu->pc + 1) + cpu->x;
	uint16_t address2 = getLEDWordAt(cpu->memory, address1);

	return address2;
}

/* indirect indexed (y) */
uint16_t resolve_iy(Processor6502* cpu)
{
	uint16_t address1 = getLEDWordAt(cpu->memory, cpu->pc + 1);
	uint16_t address2 = getByteAt(cpu->memory, address1);

	return address2;
}
