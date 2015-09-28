#ifndef MEM_H
#define MEM_H


// Library
#include <cstdint>
#include <cstdio>
#include <memory>
// Define
#define MEM_SIZE 0x0800


// ppu forward dcl
namespace ppu {
	class Ppu;
}

namespace mem {
	typedef uint8_t Word;

	class Cartridge {
	public:
		virtual void store(Word w, uint16_t addr);
		virtual Word load(uint16_t addr);
		virtual ~Cartridge();
	};

	class Mem {
 		public:
			Mem(std::unique_ptr<Cartridge> &cart);
			~Mem();

			void setPpu(ppu::Ppu * ppu);

			void store(Word w, uint16_t addr);
			void store(Word * w, size_t size, uint16_t addr);
			Word load(uint16_t addr);
			// copies an area of bank to the destination buffer. Used in DMA.
			void copy(uint16_t addr, Word * w, size_t len);
			void reset();
			void powerUp();
 		private:
			uint8_t bank[MEM_SIZE];
			std::unique_ptr<Cartridge> cart;
			ppu::Ppu * ppu;
	};
}

#endif
