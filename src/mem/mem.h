#ifndef MEM_H
#define MEM_H

// Library
#include <stdint.h>
#include <string.h>
// Define
#define MEM_SIZE 0xFFFF
#define MEM_CARTRIDGE_SPACE_ADDR 0x4020

namespace mem {
	typedef uint8_t Word;
	class Mem {
 		public:
			Mem();
			~Mem();

			void store(Word w, uint16_t addr);
			void store(Word * w, size_t size, uint16_t addr);
			Word load(uint16_t addr);
			void reset();
			void powerUp();
			uint8_t* getBank();
 		private:
			uint8_t bank[MEM_SIZE];
	};
}

#endif
