#ifndef INSTRUCTION_H
#define INSTRUCTION_H
namespace cpu{
	typedef union {
		struct
		{
			uint8_t inst;
		}s;
		struct 
		{
			char op:3;
			char operand:4;

		}m;
		struct
		{
			char op:3;
			char target:5;
		};

	} Instruction;

}
#endif
