#include "mem.h"
#include <string.h>

namespace mem {
	Mem::Mem() {
		reset();
	}

	void Mem::reset() {
		std::memset(&this->bank, 0, sizeof(this->bank));
	}

}