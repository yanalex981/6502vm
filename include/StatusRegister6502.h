#ifndef STATUS_REGISTER_6502
#define STATUS_REGISTER_6502

#define NEGATIVE		0x80
#define OVERFLOW		0x40
#define DUD				0x20
#define BREAK			0x10
#define DECIMAL			0x08
#define IRQ_DISABLED	0x04
#define ZERO			0x02
#define CARRY			0x01

/*
isNegative(Processor6502*);
overflowed(Processor6502*);
breaking(Processor6502*);
inDecimalMode(Processor6502*);
irqDisabled(Processor6502*);
isZero(Processor6502*);
isCarrying(Processor6502*);

setNegative();
setOverflow();
setBreak();
setDecimalMode();
setIRQDisabled();
setZero();
setCarry();

setNegative();
setOverflow();
setBreak();
setDecimalMode();
setIRQDisabled();
setZero();
setCarry();
*/

#endif