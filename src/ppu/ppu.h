#ifndef PPU_H
#define PPU_H


#define PPU_CTRL_ADDR 0x2000
#define PPU_CTRL_FLAG_NAMETABLE_ADDR_2000 0
#define PPU_CTRL_FLAG_NAMETABLE_ADDR_2400 1
#define PPU_CTRL_FLAG_NAMETABLE_ADDR_2800 2
#define PPU_CTRL_FLAG_NAMETABLE_ADDR_2C00 3
#define PPU_CTRL_FLAG_SPRITE_PTRN_ADDR (1<<3)
#define PPU_CTRL_FLAG_BG_PTRN_ADDR (1<<4)
#define PPU_CTRL_FLAG_SPRITE_SIZE (1<<5)
#define PPU_CTRL_FLAG_MASTER_SELECT (1<<6)
#define PPU_CTRL_FLAG_GEN_NMI (1<<7)

int GetNameTableAddr(int flag) {
	if(flag & PPU_NAMETABLE_ADDR_2000) {
		return 0x2000
	} else if (flag & PPU_NAMETABLE_ADDR_2400) {
		return 0x2400
	} else if (flag & PPU_NAMETABLE_ADDR_2800) {
		return 0x2800
	} else if (flag & PPU_NAMETABLE_ADDR_2C00) {
		return 0x2C00
	}

	return -1
}

#define PPU_MASK_ADDR 0x2001
#define PPU_MASK_FLAG_GRAYSCALE (1)
#define PPU_MASK_FLAG_SHOW_LEFTMOST_BG (1<<1)
#define PPU_MASK_FLAG_SHOW_LEFTMOST_SPRITES (1<<2)
#define PPU_MASK_FLAG_SHOW_BG (1<<3
#define PPU_MASK_FLAG_SHOW_SPRITES (1<<4)
#define PPU_MASK_FLAG_INTENSIFY_REDS (1<<5)
#define PPU_MASK_FLAG_INTENSIFY_GREENS (1<<6)
#define PPU_MASK_FLAG_INTENSIFY_GREENS (1<<7)



#endif