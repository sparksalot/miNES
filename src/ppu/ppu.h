#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include "ppu_defines.h"


namespace ppu {
	class Ppu {
 		public:
			Ppu(uint8_t * mem);
			~Ppu();
			void tick();
 		private:
			uint8_t * mem;
	};
}

#endif
