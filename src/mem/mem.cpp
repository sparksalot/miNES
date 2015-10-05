// Class
#include "mem.h"

#include "../ppu/ppu.h"

#include <cstring>
#include <cassert>
#include <iostream>

#define MEM_MIRROR_END 0x2000
#define MEM_CART_SPACE_BEGIN 0x4020
#define MEM_APU_IO_END 0x4020
#define MEM_PPU_SPACE_END 0x4000
#define MEM_PPU_SPACE_BEGIN 0x2000

namespace mem {
	Mem::Mem(std::unique_ptr<cart::Cartridge> &cart) : cart(std::move(cart)) {
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
			assert(ppu);
			
			auto ppuAddr = addr;
			// mirrored every 8 bytes. normalise to first appearance.
			if (ppuAddr > MEM_PPU_SPACE_BEGIN + 7) {
				ppuAddr = ((addr - MEM_PPU_SPACE_BEGIN) % 8) + MEM_PPU_SPACE_BEGIN;
			}

			std::cout << "MEM: ppu write to 0x" << std::hex << ppuAddr << std::endl;
			switch(ppuAddr) {
				case PPU_CTRL_ADDR: {
					ppu->setCtrl(w);
				} break;
				case PPU_MASK_ADDR: {
					ppu->setCtrl(w);
				} break;
				case PPU_OAMADDR_ADDR: {
					ppu->setOamAddr(w);
				}break;
				case PPU_OAMDATA_ADDR: {
					ppu->setOamData(w);
				}break;
				default:
					std::cerr << "MEM: unmapped ppu write to 0x" << std::hex << ppuAddr << std::endl;
				break;
			}

		} else if (addr < MEM_APU_IO_END) {
			switch(addr) {
				case PPU_DMA_ADDR: {
					assert(ppu);
					ppu->dma(w);
				}
			}

		} else { // 0x4020 space and above is the cart.
			assert(cart);
			cart->store(w, addr);
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
		} else if (addr < MEM_PPU_SPACE_END) {
			assert(ppu);
			
			auto ppuAddr = addr;
			// mirrored every 8 bytes. normalise to first appearance.
			if (ppuAddr > MEM_PPU_SPACE_BEGIN + 7) {
				ppuAddr = ((addr - MEM_PPU_SPACE_BEGIN) % 8) + MEM_PPU_SPACE_BEGIN;
			}

			std::cout << "MEM: ppu read 0x" << std::hex << ppuAddr << std::endl;
			switch(ppuAddr) {
				case PPU_STATUS_ADDR:
				return ppu->getStatus();
				default:
					std::cerr << "MEM: unmapped ppu read 0x" << std::hex << ppuAddr << std::endl;
					assert(false);
				break;
			}

		} else if (addr < MEM_APU_IO_END) {
			switch(addr) {
				case PPU_DMA_ADDR: return 0;
			}
		} else { // 0x4020 space and above is the cart.
			assert(cart);
			return cart->load(addr);
		}

		std::cerr << "MEM: Attempted to read unmapped memory addr: 0x" << std::hex << addr << std::endl;
		assert(false);
		return 0;
	}

	void Mem::copy(uint16_t addr, Word * w, size_t len) {
		for(size_t i = 0; i < len; i++) {
			w[i] = Mem::load(i+addr);
		}
	}

	void Mem::setPpu(ppu::Ppu * ppu) {
		this->ppu = ppu;
	}
}
