#ifndef CPU_H
#define CPU_H

// Library
#include <stdint.h>
// Project
#include "instruction.h"
#include "../mem/mem.h"
#include "programcounter.h"
// Define
#define STACK_BASE 0x0100

namespace cpu {
	class Cpu
	{
	public:
		Cpu();
		void tick(void);
		void fetch(void);
		void loadInstuction(Instruction i);
		void execute(Instruction i);
		~Cpu();
	private:
		Instruction next;
		ProgramCounter counter;
		uint8_t accumulator;
		uint8_t x, y;
		mem::Mem mem;
		uint8_t sp;
		uint8_t status;
	};

}

#endif
