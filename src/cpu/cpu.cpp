// Class
#include "cpu.h"
// Library
#include <string.h>
#include <stdio.h>

#include "../mem/mem.h"
// Define
#define CPU_INCREMENT 1

namespace cpu {
	Cpu::Cpu() {
		counter.pc = 0;
		next.inst = 0;
		accumulator = 0;  // nesdev
		x = 0;  // nesdev
		y = 0;  // nesdev
		status = 0x34;  // nesdev, P = $34 (IRQ disabled)*
		sp = 0xFD;  // nesdev, S = $FD
	}

	void Cpu::reset(void) {
		if (sp >= 3)
			sp -= 3;  // nesdev, S was decremented by 3 (but nothing was written to the stack)
		else
			sp = 0;
		//TODO nesdev, The I (IRQ disable) flag was set to true (status ORed with $04)

		counter.pc = 0;
		next.inst = 0;
		x = 0;
		y = 0;
		accumulator = 0;
		sp = 0;
		status = 0;
		mem.reset();
	}

	Cpu::~Cpu() {
	}

	void Cpu::tick() {
		printf("Current program counter is: %i\n", counter.pc);
		fetch();
		this->execute(this->next);
		counter.pc = counter.pc + CPU_INCREMENT;
	}

	void Cpu::execute(Instruction i) {

	}

	void Cpu::fetch() {
		mem::Word n = mem.load(this->counter.pc);
		memcpy(&this->next, &n, sizeof(this->next));
	}
}
