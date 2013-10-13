#include "mem.h"
#include <cstring>

namespace mem {
	Mem::Mem() {
		reset();
	}

	void Mem::reset() {
		std::memset(&this->bank, 0, sizeof(bank));
	}

}
