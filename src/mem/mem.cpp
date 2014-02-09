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
		bank[MEM_FRAME_IRQ] = 0x00;  // frame irq enabled
		bank[MEM_RESET_APU] = 0x00;  // silence APU
		memset(&bank[0x4000], 0x00, sizeof(Word) * 0x10);
		// changes not shown here also include a, x, y to 0, s to $fd, p to $34
	}

	void Mem::reset() {
		bank[MEM_RESET_APU] = 0x00;  // silence APU
		// changes not shown here also include S=S-3, IRQ disable flag to true (OR'd with $04)
	}

	void Mem::store(const uint16_t addr, Word w) {
		this->bank[decodeMirror(addr)] = w;
	}

	//TODO() Need to do the conditional mirrors, http://wiki.nesdev.com/w/index.php/Mirroring#Memory_Mirroring
	uint16_t Mem::decodeMirror(const uint16_t& addr) {
		static const uint16_t main_mem_size = 0x0800, ppu_reg_size = 0x0008;

		// Memory mirroring doesn't occur until 0x0800
		if (addr <= 0x07FF) return addr; // 0x0000 to 0x07FF

		// System memory at $0000-$07FF is mirrored at $0800-$0FFF, $1000-$17FF, and $1800-$1FFF
		if (/*addr >= 0x0000 && */addr <= 0x1FFF) {
			if (addr <= 0x7FF) return addr;
			else return (addr - (main_mem_size * (addr / main_mem_size)));
		}

		// PPU I/O registers at $2000-$2007 are mirrored from $0800 to $3FFF over and over
		if (addr >= 0x2000 && addr <= 0x3FFF) {
			if (addr <= 0x2007) return addr;
			else return (addr - (ppu_reg_size * (addr / ppu_reg_size)));
		}

		return addr; // This will never hit, but the compiler will complain without it
	}

	//TODO() guard against (addr+i) >= max address
	//TODO() consider changing for loop+assignment to a memcpy()
	void Mem::store(const uint16_t addr, Word * w, size_t size) {
		for(size_t i = 0; i < size; ++i) {
			bank[decodeMirror(addr+i)] = w[i];
		}
	}

	Word Mem::load(const uint16_t addr) {
		return bank[decodeMirror(addr)];
	}
}
