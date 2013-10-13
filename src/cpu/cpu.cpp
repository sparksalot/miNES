// Class
#include "cpu.h"
// Library
#include <string.h>
// Define
#define CPU_INCREMENT 4


namespace cpu {
	Cpu::Cpu() {
		counter.pc = 0;
		next.inst = 0;
		x = 0;
		y = 0;
		accumulator = 0;
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
