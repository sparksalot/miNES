#ifndef MEM_H
#define MEM_H

// Library
#include <stdint.h>
#include <string.h>
// Define
#define MEM_SIZE 0xFFFF
#define MEM_RESET_APU 0x4015
#define MEM_FRAME_IRQ 0x4017

namespace mem {
	typedef uint8_t Word;
	class Mem {
 		public:
			Mem();
			~Mem();

			void store(const uint16_t addr, Word w);
			void store(const uint16_t addr, Word * w, size_t size);
			Word load(const uint16_t addr);
			void reset();
			void powerUp();
			uint16_t decodeMirror(const uint16_t& addr);
 		private:
			uint8_t bank[MEM_SIZE];
	};
}

#endif
