// Class
#include "mem.h"
// Library
#include <string.h>

namespace mem {
	Mem::Mem() {
		reset();
	}

	Mem::~Mem() {

	}

	void Mem::reset() {
		memset(&this->bank, 0xff, sizeof(Word) * 0x7ff);
		bank[0x0008] = 0xF7;
		bank[0x0009] = 0xEF;
		bank[0x000a] = 0xDF;
		bank[0x000f] = 0xBF;
		bank[0x4017] = 0x00;
		bank[0x4015] = 0x00;
		memset(&bank[0x4000], 0x00, sizeof(Word) * 0xf);
	}
}
