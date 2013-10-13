#include "cpu.h"

#define CPU_INCREMENT 4

namespace cpu {
	void Cpu::Cpu() {
		memset(&this->next, 0, sizeof(this->next));
	}

	void Cpu::tick() {
		fetch();
		execute(this->next);
		counter.pc = counter.pc + CPU_INCREMENT;
	}

	void Cpu::execute(Instruction i) {
		
	}

	void Cpu::fetch() {

	}
}
