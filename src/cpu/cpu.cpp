#include "cpu.h"
#include <string.h>

#define CPU_INCREMENT 4


namespace cpu {
	Cpu::Cpu() {
		memset(&this->next, 0, sizeof(this->next));
		sp = 0;
		status = 0;
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
