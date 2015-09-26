// Class
#include "cpu.h"
// Library
#include <string.h>
#include <stdio.h>

#include "../mem/mem.h"
// Define

namespace cpu {
	Cpu::Cpu() : 
	next(0),
	counter({0}), 
	accumulator(0), 
	x(0), // nesdev
	y(0), // nesdev
	mem(new mem::Mem()),
	sp(0xFD), // nesdev, S = $FD
	status(0x34), // nesdev, P = $34 (IRQ disabled)*
	operations({0})
	{ }

	void Cpu::reset() {
		if (sp >= 3)
			sp -= 3;  // nesdev, S was decremented by 3 (but nothing was written to the stack)
		else
			sp = 0;
		//TODO nesdev, The I (IRQ disable) flag was set to true (status ORed with $04)

		counter.pc = 0;
		next = 0;
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
		this->fetch();
		this->execute(this->next);
	}

	void Cpu::execute(Instruction i) {

		if(!operations[i]) {
			printf("No operation.  (0x%x)\n", i);
			return;
		}
		operations[i]();
	}

	void Cpu::fetch() {
		this->next = (Instruction)mem->load(this->counter.pc);
		++this->counter.pc;
	}
}
