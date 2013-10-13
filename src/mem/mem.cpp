// Class
#include "mem.h"

namespace mem {
	Mem::Mem() {
		powerUp();
	}

	Mem::~Mem() {

	}
	void Mem::powerUp() {
		memset(&this->bank, 0xff, sizeof(Word) * 0x800);
		bank[0x0008] = 0xF7;
		bank[0x0009] = 0xEF;
		bank[0x000a] = 0xDF;
		bank[0x000f] = 0xBF;
		bank[0x4017] = 0x00;  // frame irq enabled
		bank[0x4015] = 0x00;  // silence APU
		memset(&bank[0x4000], 0x00, sizeof(Word) * 0x10);
		// changes not shown here also include a, x, y to 0, s to $fd, p to $34
	}

	void Mem::reset() {
		;
		bank[0x4015] = 0x00;  // silence APU
		// changes not shown here also include S=S-3, IRQ disable flag to true (OR'd with $04)
	}

	void Mem::store(Word w, uint16_t addr) {
		this->bank[addr] = w;
	}

	void Mem::store(Word * w, size_t size, uint16_t addr) {
		for(int i = 0; i < size; ++i) {
			bank[i] = w[i];
		}
	}

	Word Mem::load(uint16_t addr) {
		return bank[addr];
	}
}
