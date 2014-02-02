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
			uint8_t vram[PPU_VRAM_SIZE];
			uint8_t oam[PPU_OAM_NUM_SPRITES][PPU_OAM_NUM_BYTES];
	};
}

#endif
