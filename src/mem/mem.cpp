#include "mem.h"

namespace mem {
	void Mem::Mem() {
		reset();
	}

	void Mem::reset() {
		memset(&this->store, 0, sizeof(this->store));
	}


}