#ifndef STATUS_REGISTER_6502
#define STATUS_REGISTER_6502

#include <stdint.h>
#include <stdbool.h>

struct StatusRegister6502;
typedef struct StatusRegister6502 StatusRegister6502;

void initStatus6502(StatusRegister6502* self);

void setStatusByte(StatusRegister6502* self, uint8_t status);
uint8_t getStatusByte(const StatusRegister6502* self);

bool isNegative(const StatusRegister6502* self);
bool overflowing(const StatusRegister6502* self);
bool breaking(const StatusRegister6502* self);
bool inDecimalMode(const StatusRegister6502* self);
bool isIRQdisabled(const StatusRegister6502* self);
bool isZero(const StatusRegister6502* self);
bool isCarrying(const StatusRegister6502* self);

void setNegative(StatusRegister6502* self);
void setOverflow(StatusRegister6502* self);
void setBreak(StatusRegister6502* self);
void setDecimalMode(StatusRegister6502* self);
void setIRQDisabled(StatusRegister6502* self);
void setZero(StatusRegister6502* self);
void setCarry(StatusRegister6502* self);

void clearNegative(StatusRegister6502* self);
void clearOverflow(StatusRegister6502* self);
void clearBreak(StatusRegister6502* self);
void clearDecimalMode(StatusRegister6502* self);
void clearIRQ(StatusRegister6502* self);
void clearZero(StatusRegister6502* self);
void clearCarry(StatusRegister6502* self);
#endif