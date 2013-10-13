#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Library
#include <stdint.h>

namespace cpu{
	typedef union {
		uint8_t inst;
		struct 
		{
			char op:3;
			char operand:4;

		}m;
	} Instruction;

}
#endif
