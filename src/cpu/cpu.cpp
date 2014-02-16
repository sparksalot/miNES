// Class
#include "cpu.h"
// Library
#include <string.h>
#include <stdio.h>

// Project
#include "../mem/mem.h"
// Define

namespace cpu {
	Cpu::Cpu() {
		counter.pc = 0;
		next = 0;
		accumulator = 0;  // nesdev
		x = 0;  // nesdev
		y = 0;  // nesdev
		status = 0x34;  // nesdev, P = $34 (IRQ disabled)*
		sp = 0xFD;  // nesdev, S = $FD

		memset(operations, 0, sizeof(operations));
	}

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
		fetch();
		this->execute(this->next);
	}

	void Cpu::execute(Instruction i) {

		if (!operations[i]) {
			printf("No operation.  (0x%x)\n", i);
			return;
		}
		operations[i]();
	}

	void Cpu::setCarryFlag() {
		setFlag(CPU_FLAG_CARRY);
	}

	void Cpu::setDecimalFlag() {
		setFlag(CPU_FLAG_DECIMAL);
	}

	void Cpu::setInteruptDisableFlag() {
		setFlag(CPU_FLAG_INTERRUPT_DISABLE);
	}


	void Cpu::fetch() {
		this->next = (Instruction) mem.load(this->counter.pc);
		++this->counter.pc;
	}

	inline void Cpu::setFlag(const unsigned int flag) {
		status |= flag;
	}

	void Cpu::transferRegister(uint8_t& dest, uint8_t& src) {
		dest = src;
		if (!src)
			setFlag(CPU_FLAG_ZERO_RESULT);
		if (GETBIT(src, 7))
			setFlag(CPU_FLAG_NEGATIVE_RESULT);
		counter.pc += 1;
	}

	void Cpu::storeRegister(uint16_t dest, uint8_t& src) {
		mem.store(dest, src);
	}
}
