#ifndef MEMORY16
#define MEMORY16

#include <stdio.h>
#include <stdint.h>

struct Memory16;
typedef struct Memory16 Memory16;

Memory16* constructMemory(Memory16* self, uint16_t size);
void destructMemory(Memory16** self);

uint8_t getByteAt(Memory16* self, uint16_t address);
void setByteAt(Memory16* self, uint16_t address, uint8_t value);

uint16_t getLEDWordAt(Memory16* self, uint16_t address);
void setLEDWordAt(Memory16* self, uint16_t address, uint16_t value);

uint16_t getBEDWordAt(Memory16* self, uint16_t address);
void setBEDWordAt(Memory16* self, uint16_t address, uint8_t value);

void dump(Memory16* self, FILE* out);
void dumpi(Memory16* self, FILE* out, size_t width);

#endif