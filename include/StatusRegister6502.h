#ifndef STATUS_REGISTER_6502
#define STATUS_REGISTER_6502

#define NEGATIVE	0x80
#define OVERFLOW	0x40
#define DUD		0x20
#define BREAK		0x10
#define DECIMAL		0x08
#define IRQ_DISABLED	0x04
#define ZERO		0x02
#define CARRY		0x01

// uint8_t getStatusByte(StatusRegister6502* self);

bool isNegative(Processor6502*);
bool overflowed(Processor6502*);
bool breaking(Processor6502*);
bool inDecimalMode(Processor6502*);
bool irqDisabled(Processor6502*);
bool isZero(Processor6502*);
bool isCarrying(Processor6502*);

void setNegative();
void setOverflow();
void setBreak();
void setDecimalMode();
void setIRQDisabled();
void setZero();
void setCarry();

void clearNegative();
void clearOverflow();
void clearBreak();
void clearDecimalMode();
void clearIRQ();
void clearZero();
void clearCarry();

#endif
