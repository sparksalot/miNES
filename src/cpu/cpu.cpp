#include "cpu.h"

namespace cpu {
	void Cpu::Cpu() {
		memset(&this->next, 0, sizeof(this->next));
	}

	void Cpu::tick() {
		execute(this->next);

	}

	void Cpu::execute(Instruction i) {
		
	}

	void Cpu::fetch() {

	}
}