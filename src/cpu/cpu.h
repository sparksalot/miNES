#ifndef CPU_H
#define CPU_H

// Library
#include <cstdint>
// Project
#include "../mem/mem.h"
#include "programcounter.h"
// Define
#define STACK_BASE 0x0100
#define MAX_OPERATIONS 0xFF

#define CPU_FLAG_CARRY (1<<0)
#define CPU_FLAG_ZERO_RESULT (1<<1)
#define CPU_FLAG_INTERRUPT_DISABLE (<<2)
#define CPU_FLAG_DECIMAL_MODE (1<<3)
#define CPU_FLAG_BREAK_COMMAND (1<<4)
#define CPU_FLAG_EXPANSION (1<<5)
#define CPU_FLAG_OVERFLOW (1<<6)
#define CPU_FLAG_NEGATIVE_RESULT (1<<7)

namespace cpu {
	typedef void (*Operation)();
	typedef uint8_t Instruction;
	class Cpu {
 		public:
		Cpu(mem::Mem * mem);
		void tick();
		void fetch();
		void loadInstuction(Instruction i);
		void execute(Instruction i);
		void reset();
		~Cpu();

		private:
		Instruction next;
		ProgramCounter counter;
		uint8_t accumulator;
		uint8_t x, y;
		mem::Mem * mem;
		uint8_t sp;  // nesdev calls it S
		uint8_t status;  // nesdev calls it P
		Operation operations[MAX_OPERATIONS];
	};

}

#endif
