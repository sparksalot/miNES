#ifndef _H_PPU
#define _H_PPU

#include "../mem/mem.h"

#include <cstdint>

#define PPU_VRAM_SIZE 0x3FFF
#define PPU_OAM_NUM_SPRITES 64
#define PPU_SECONDARY_OAM_NUM_SPRITES 8
#define PPU_OAM_NUM_BYTES 4
#define PPU_OAM_DMA_ADDR 0x4014

#define PPU_CTRL_ADDR 0x2000
#define PPU_MASK_ADDR 0x2001
#define PPU_STATUS_ADDR 0x2002
#define PPU_OAMADDR_ADDR 0x2003
#define PPU_OAMDATA_ADDR 0x2004

#define PPU_DMA_ADDR 0x4014

namespace ppu {

	class Ppu
	{
	public:
		Ppu(mem::Mem * mem);
		// performs a ppu tick.
		void tick();

		// performs a ppu reset
		void reset();

		// does a dma write to the ppu OAM.
		void dma(uint8_t h);

		void setCtrl(uint8_t ctrl);

		void setMask(uint8_t ctrl);

		uint8_t getStatus();

		// OAM address that will be writen to by following writes to OAMDATA
		void setOamAddr(uint8_t addr);
		// Write data to OAMADDR
		void setOamData(uint8_t data);

		~Ppu();
	private:
		mem::Mem *bank;
		bool odd;
		int16_t scanline;
		int16_t cycle;
		uint8_t vram[PPU_VRAM_SIZE];
		uint8_t oam[PPU_OAM_NUM_SPRITES][PPU_OAM_NUM_BYTES];
		uint8_t secondaryOam[PPU_SECONDARY_OAM_NUM_SPRITES][PPU_OAM_NUM_BYTES];
		uint8_t ctrl;
		uint8_t mask;
		uint8_t status;
		uint8_t oamaddr;
	};
}

#endif
