#ifndef CPU_H
#define CPU_H
// Library
#include <stdint.h>
// Project
#include "instruction.h"
#include "programcounter.h"

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
		ProgramCounter pc;
	};

}

#endif
