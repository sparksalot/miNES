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
		powerUp();
	}

	void Cpu::powerUp(void) {
		accumulator = 0; // nesdev
		x = 0; // nesdev
		y = 0; // nesdev
		status = 0x34; // nesdev, P = $34 (IRQ disabled)*
		sp = 0xFD; // nesdev, S = $FD
	}

	void Cpu::reset(void) {
		if (sp >= 3) sp -= 3; // nesdev, S was decremented by 3 (but nothing was written to the stack)
		else sp = 0;
		//TODO nesdev, The I (IRQ disable) flag was set to true (status ORed with $04)
	}

	Cpu::~Cpu() {

	}

	void Cpu::tick(void) {
		fetch();
		this->execute(this->next);
		counter.pc = counter.pc + CPU_INCREMENT;
	}

	void Cpu::execute(Instruction i) {
		
	}

	void Cpu::fetch() {

	}
}
