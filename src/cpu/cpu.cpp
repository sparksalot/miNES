#include "cpu.h"
#include <string.h>

#define CPU_INCREMENT 4

namespace cpu {
	Cpu::Cpu() {
		counter.pc = 0;
		next.inst = 0;
		x = 0;
		y = 0;
		accumulator = 0;
		memset(&this->next, 0, sizeof(this->next));
	}

	Cpu::~Cpu() {

	}

	void Cpu::tick() {
		fetch();
		this->execute(this->next);
		counter.pc = counter.pc + CPU_INCREMENT;
	}

	void Cpu::execute(Instruction i) {
		
	}

	void Cpu::fetch() {

	}
}
