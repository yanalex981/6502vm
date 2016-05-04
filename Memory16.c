#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Memory16.h"

struct Memory16
{
	uint8_t* bytes;
	uint16_t size;
};

Memory16 *mkMemory(uint16_t size)
{
	Memory16 *memory = malloc(sizeof(Memory16));

	memory->bytes = calloc(size, sizeof(uint8_t));
	memory->size = size;

	return memory;
}

Memory16 *mkMemoryFrom(uint8_t *image, size_t imgSize, uint16_t size)
{
	Memory16 *memory = mkMemory(size);

	for (size_t i = 0; i < imgSize; ++i)
		memory->bytes[i] = image[i];

	return memory;
}

void delMemory(Memory16** self)
{
	free((*self)->bytes);
	free(*self);
}

uint8_t getByteAt(Memory16* self, uint16_t address)
{
	if (address > self->size)
		return 0;
	
	return self->bytes[address];
}

void setByteAt(Memory16* self, uint16_t address, uint8_t value)
{
	if (address < self->size)
		self->bytes[address] = value;
}

uint16_t getLEWordAt(Memory16* self, uint16_t address)
{
	uint16_t word = getByteAt(self, address + 1);
	word <<= 8;
	word |= getByteAt(self, address);

	return word;
}

void setLEWordAt(Memory16* self, uint16_t address, uint16_t value)
{
	uint8_t low = value & 0x00FF;
	uint8_t high = (value & 0xFF00) >> 8;

	setByteAt(self, address, low);
	setByteAt(self, address + 1, high);
}

uint16_t getBEWordAt(Memory16* self, uint16_t address)
{
	uint16_t word = getByteAt(self, address);
	word <<= 8;
	word |= getByteAt(self, address + 1);

	return word;
}

void setBEWordAt(Memory16* self, uint16_t address, uint16_t value)
{
	uint8_t low = value & 0x00FF;
	uint8_t high = (value & 0xFF00) >> 8;

	setByteAt(self, address, high);
	setByteAt(self, address + 1, low);
}

void dumpi(Memory16* self, FILE* out, size_t width)
{
	for (int i = 0; i < self->size; ++i) {
		printf("%u", self->bytes[i]);

		if (i % width != 0)
			printf(" ");
		else
			printf("\n");
	}
}

void dump(Memory16* self, FILE* out)
{
	dumpi(self, out, 40);
}