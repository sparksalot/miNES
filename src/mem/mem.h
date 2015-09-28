#ifndef MEM_H
#define MEM_H

// Library
#include <cstdint>
#include <cstdio>
// Define
#define MEM_SIZE 0x0800

namespace mem {
	typedef uint8_t Word;

	class Mem {
 		public:
			Mem();
			~Mem();

			void store(Word w, uint16_t addr);
			void store(Word * w, size_t size, uint16_t addr);
			Word load(uint16_t addr);
			// copies an area of bank to the destination buffer. Used in DMA.
			void copy(uint16_t addr, Word * w, size_t len);
			void reset();
			void powerUp();
 		private:
			uint8_t bank[MEM_SIZE];
	};
}

#endif
