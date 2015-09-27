#include "ppu.h"

#include <cstring>
#include <iostream>

#define PPU_CTRL_ADDR 0x2000


#define PPU_MASK_ADDR 0x2001

#define PPU_STATUS_ADDR 0x2002
#define PPU_STATUS_VBLANK (1<<7)

#define CYCLE_MAX 340

using namespace ppu;

Ppu::Ppu(mem::Mem * mem):bank(mem), odd(false), scanline(-1), cycle(0) {
	bank->store(0, PPU_CTRL_ADDR);
	bank->store(0, PPU_MASK_ADDR);
}

Ppu::~Ppu() {

}

void Ppu::tick() {
	
	if (scanline == -1) { // dummy

	} else if (scanline < 240 ) { // visible scanline

	} else if (scanline == 240) { // idle

	} else if (scanline < 260) { // vblank
		if (cycle == 0 && scanline == 241)
		{
			std::cout << "PPU: vblank started" << std::endl;
			auto t = bank->load(PPU_STATUS_ADDR);
			t &= PPU_STATUS_VBLANK;
			bank->store(t, PPU_STATUS_ADDR);
		}
	} else { // 261, dummy, pre-scanline
		if (cycle == 0)
		{
			std::cout << "PPU: vblank ended" << std::endl;
			auto t = bank->load(PPU_STATUS_ADDR);
			t &= ~PPU_STATUS_VBLANK;
			bank->store(t, PPU_STATUS_ADDR);

		}
	}

	cycle++;
	if (cycle == CYCLE_MAX) {
		scanline++;
		cycle = 0;
		if (scanline == 262) {
			scanline = 0;
		} 
	}

	odd = !odd;
}

void Ppu::reset() {
	bank->store(0, PPU_CTRL_ADDR);
	bank->store(0, PPU_MASK_ADDR);
	odd = false;
}

void Ppu::dma() {
	uint16_t addr = ((uint16_t)bank->load(PPU_OAM_DMA_ADDR)) << 8;

	std::cout << "PPU: DMA from 0x" <<std::hex << addr << std::endl;

	bank->copy(addr, &oam[0][0], sizeof(oam));
	bank->store(0, PPU_OAM_DMA_ADDR);
}
