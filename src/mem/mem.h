#ifndef MEM_H
#define MEM_H

// Library
#include <stdint.h>
#include <string.h>
// Define
#define MEM_SIZE 0xFFFF

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
 		private:
			uint8_t bank[MEM_SIZE];
	};
}

#endif
