#ifndef _H_PPU
#define _H_PPU

#include "../mem/mem.h"

namespace ppu {
	class Ppu
	{
	public:
		Ppu(mem::Mem * mem);
		void tick();
		~Ppu();
	private:
		mem::Mem *bank;
	};
}

#endif
