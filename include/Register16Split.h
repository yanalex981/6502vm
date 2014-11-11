#ifndef REGISTER16SPLIT
#define REGISTER16SPLIT

#include <stdint.h>

uint8_t highByteOf(uint16_t self);
uint8_t lowByteOf(uint16_t self);
void setHighByteOf(uint16_t* self, uint8_t word);
void setLowByteOf(uint16_t* self, uint8_t word);

#endif