#ifndef MEMORY16
#define MEMORY16

#include <stdio.h>
#include <stdint.h>

typedef struct Memory16 Memory16;

Memory16 *mkMemory(uint16_t size);
Memory16 *mkMemoryFrom(uint8_t *image, size_t imgSize, uint16_t size);
void delMemory(Memory16** self);

uint8_t getByteAt(Memory16* self, uint16_t address);
void setByteAt(Memory16* self, uint16_t address, uint8_t value);

uint16_t getLEWordAt(Memory16* self, uint16_t address);
void setLEWordAt(Memory16* self, uint16_t address, uint16_t value);

uint16_t getBEWordAt(Memory16* self, uint16_t address);
void setBEWordAt(Memory16* self, uint16_t address, uint16_t value);

void dumpi(Memory16* self, FILE* out, size_t width);
void dump(Memory16* self, FILE* out);

#endif