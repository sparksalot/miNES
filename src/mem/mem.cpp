#include "mem.h"
#include <string.h>

namespace mem {
	Mem::Mem() {
		reset();
	}

	Mem::~Mem() {

	}

	void Mem::reset() {
		memset(&this->bank, 0, sizeof(this->bank));
	}

}
