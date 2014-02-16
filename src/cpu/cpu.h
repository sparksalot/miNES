#ifndef CPU_H
#define CPU_H

// Library
#include <stdint.h>
// Project
#include "../mem/mem.h"
#include "programcounter.h"
// Define
#define STACK_BASE 0x0100
#define MAX_OPERATIONS 0xFF

#define CPU_FLAG_CARRY (1<<0)
#define CPU_FLAG_ZERO_RESULT (1<<1)
#define CPU_FLAG_INTERRUPT_DISABLE (1<<2)
#define CPU_FLAG_DECIMAL (1<<3)
#define CPU_FLAG_BREAK_COMMAND (1<<4)
#define CPU_FLAG_EXPANSION (1<<5)
#define CPU_FLAG_OVERFLOW (1<<6)
#define CPU_FLAG_NEGATIVE_RESULT (1<<7)

#define GETBIT(x,y) (x & (1<<y))

namespace cpu {
	typedef void (*Operation)();
	typedef uint8_t Instruction;
	class Cpu {
 		public:
			Cpu();
			~Cpu();
			// Core
			void tick();
			void fetch();
			void loadInstuction(Instruction i);
			void execute(Instruction i);
			void reset();
			// Convinience
			inline void clearFlag(const uint8_t flag);
			inline void setFlag(const uint8_t flag);
			inline bool getFlag(const uint8_t flag);
			void compare(uint16_t& lValueAddress, uint8_t rvalue);
			void transferRegister(uint8_t& dest, uint8_t& src, bool setFlags);

			// Operations
			void AND(uint16_t& src);
			void ADC(uint16_t& src);
			void ASL(uint16_t& src);
			void BCC(int8_t& offset);
			void BCS(int8_t& offset);
			void BEQ(int8_t& offset);
			void BIT(uint16_t& src);
			void BMI(int8_t& offset);
			void BNE(int8_t& offset);
			void BPL(int8_t& offset);
			void BRK();
			void BVC(int8_t& offset);
			void BVS(int8_t& offset);
			void CLC();
			void CLD();
			void CLI();
			void CLV();
			void CMP(uint16_t& src);
			void CPX(uint16_t& src);
			void CPY(uint16_t& src);

			void SEC();
			void SED();
			void SEI();
			void STA(uint16_t dest);
			void STX(uint16_t dest);
			void STY(uint16_t dest);
			void TAX();
			void TAY();
			void TSX();
			void TXA();
			void TXS();
			void TYA();

 		private:
			Instruction next;
			ProgramCounter counter;
			uint8_t accumulator;
			uint8_t x, y;
			mem::Mem mem;
			uint8_t sp;  // nesdev calls it S
			uint8_t status;  // nesdev calls it P
			Operation operations[MAX_OPERATIONS];
	};

}

#endif
