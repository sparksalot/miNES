#ifndef CPU_H
#define CPU_H

#include "instruction.h"
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
		uint16_t pc;
		Instuction next;
	};

}

#endif