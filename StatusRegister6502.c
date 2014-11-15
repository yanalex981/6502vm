#include <stdint.h>
#include <stdlib.h>

#include "StatusRegister6502.h"

#define NEGATIVE	0x80
#define OVERFLOW	0x40
#define DUD		0x20
#define BREAK		0x10
#define DECIMAL		0x08
#define IRQ		0x04
#define ZERO		0x02
#define CARRY		0x01

typedef struct StatusRegister6502
{
	uint8_t status;
} StatusRegister6502;

void constructStatus(StatusRegister6502** self)
{
	*self = malloc(sizeof(StatusRegister6502));

	(*self)->status = DUD;
}

void destructStatus(StatusRegister6502** self)
{
	free(*self);

	*self = NULL;
}

void setStatusByte(StatusRegister6502* self, uint8_t status)
{
	self->status = status | DUD;
}

uint8_t getStatusByte(const StatusRegister6502* self)
{
	return self->status;
}

// GETTER
bool isNegative(const StatusRegister6502* self)
{
	return (self->status & NEGATIVE)? true : false;
}

bool overflowing(const StatusRegister6502* self)
{
	return (self->status & OVERFLOW)? true : false;
}

bool breaking(const StatusRegister6502* self)
{
	return (self->status & BREAK)? true : false;
}

bool inDecimalMode(const StatusRegister6502* self)
{
	return (self->status & DECIMAL)? true : false;
}

bool isIRQdisabled(const StatusRegister6502* self)
{
	return (self->status & IRQ)? true : false;
}

bool isZero(const StatusRegister6502* self)
{
	return (self->status & ZERO)? true : false;
}

bool isCarrying(const StatusRegister6502* self)
{
	return (self->status & CARRY)? true : false;
}
// SETTER
void setNegative(StatusRegister6502* self)
{
	self->status = self->status | NEGATIVE;
}

void setOverflow(StatusRegister6502* self)
{
	self->status = self->status | OVERFLOW;
}

void setBreak(StatusRegister6502* self)
{
	self->status = self->status | BREAK;
}

void setDecimalMode(StatusRegister6502* self)
{
	self->status = self->status | DECIMAL;
}

void setIRQDisabled(StatusRegister6502* self)
{
	self->status = self->status | IRQ;
}

void setZero(StatusRegister6502* self)
{
	self->status = self->status | ZERO;
}

void setCarry(StatusRegister6502* self)
{
	self->status = self->status | CARRY;
}

// CLEARER
void clearNegative(StatusRegister6502* self)
{
	self->status = self->status & ~NEGATIVE;
}

void clearOverflow(StatusRegister6502* self)
{
	self->status = self->status & ~OVERFLOW;
}

void clearBreak(StatusRegister6502* self)
{
	self->status = self->status & ~BREAK;
}

void clearDecimalMode(StatusRegister6502* self)
{
	self->status = self->status & ~DECIMAL;
}

void clearIRQ(StatusRegister6502* self)
{
	self->status = self->status & ~IRQ;
}

void clearZero(StatusRegister6502* self)
{
	self->status = self->status & ~ZERO;
}

void clearCarry(StatusRegister6502* self)
{
	self->status = self->status & ~CARRY;
}