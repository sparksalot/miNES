#ifndef CPU_H
#define CPU_H

#include "instruction.h"
#include "../mem/mem.h"
#include "programcounter.h"
#include <stdint.h>

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
	};

}

#endif
