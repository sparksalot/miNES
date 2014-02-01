#include "ppu.h"

int GetNameTableAddr(int flag) {
	if(flag & PPU_CTRL_FLAG_NAMETABLE_ADDR_2000) {
		return 0x2000;
	} else if (flag & PPU_CTRL_FLAG_NAMETABLE_ADDR_2400) {
		return 0x2400;
	} else if (flag & PPU_CTRL_FLAG_NAMETABLE_ADDR_2800) {
		return 0x2800;
	} else if (flag & PPU_CTRL_FLAG_NAMETABLE_ADDR_2C00) {
		return 0x2C00;
	}

	return -1;
}



namespace ppu {
	Ppu::Ppu(uint8_t * mem) {
		this->mem = mem;
	}

	void Ppu::tick() {

	}

	Ppu::~Ppu() {
	}

}
