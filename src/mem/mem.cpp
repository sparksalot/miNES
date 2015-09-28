// Class
#include "mem.h"

#include <cstring>
#include <cassert>
#include <iostream>

#define MEM_MIRROR_END 0x2000
#define MEM_CART_SPACE_BEGIN 0x4020
#define MEM_APU_IO_END 0x4020
#define MEM_PPU_SPACE_END 0x4000
#define MEM_PPU_SPACE_BEGIN 0x2000

namespace mem {
	Mem::Mem() {
		powerUp();
	}

	Mem::~Mem() {

	}
	void Mem::powerUp() {
		memset(&this->bank, 0xff, sizeof(bank));
		store(0xF7, 0x0008);
		store(0xEF, 0x0009);
		store(0xDF, 0x000a);
		store(0xBF, 0x000f);
		store(0x00, 0x4017);  // frame irq enabled
		store(0x00, 0x4015);  // silence APU

		// blank apu and ir registers. 
		//memset(&bank[0x4000], 0x00, sizeof(Word) * 0x10);
		// changes not shown here also include a, x, y to 0, s to $fd, p to $34
	}

	void Mem::reset() {
		store(0x00,0x4015); // silence APU
		// changes not shown here also include S=S-3, IRQ disable flag to true (OR'd with $04)
	}

	void Mem::store(Word w, uint16_t addr) {
		if(addr < MEM_MIRROR_END) {
			this->bank[addr % MEM_SIZE] = w;
		} else if (addr < MEM_PPU_SPACE_END) {
			// mirrored every 8 bytes.
			auto ppuAddr = (addr - MEM_PPU_SPACE_BEGIN) % 8;
			std::cout << "MEM: ppu write to 0x" << std::hex << ppuAddr << std::endl;

		} else if (addr < MEM_APU_IO_END) {

		} else { // 0x4020 space and above is the cart.
			std::cerr << "MEM: Attempted to write unmapped memory addr: 0x" << std::hex << addr << std::endl;
			assert(false);
		}
	}

	//TODO(nick) guard against (addr+i) >= max address
	//TODO(nick) consider changing for loop+assignment to a memcpy()
	void Mem::store(Word * w, size_t size, uint16_t addr) {
		for(size_t i = 0; i < size; ++i) {
			store(w[i], addr+i);
		}
	}

	Word Mem::load(uint16_t addr) {
		if(addr < MEM_MIRROR_END) {
			return this->bank[addr % MEM_SIZE];
		}

		//TODO(jake) write mappings for apu/ppu/cartspace

		std::cerr << "MEM: Attempted to read unmapped memory addr: 0x" << std::hex << addr << std::endl;
		assert(false);
		return 0;
	}

	void Mem::copy(uint16_t addr, Word * w, size_t len) {
		for(size_t i = 0; i < len; i++) {
			w[i] = Mem::load(i+addr);
		}
	}
}
