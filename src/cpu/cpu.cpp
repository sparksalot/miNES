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

	void Cpu::storeRegisterZeroPage(uint8_t dest, uint8_t& src) {
		storeRegister((uint16_t) (0x00FF & dest), src);
		counter.pc += 2;
	}

	//TODO() needs to account for wrapping over 0xFF! http://www.obelisk.demon.co.uk/6502/addressing.html#ZPX
	void Cpu::storeRegisterZeroPageX(uint8_t dest, uint8_t& src) {
		storeRegister((uint16_t) (0x00FF & (dest + x)), src);
		counter.pc += 2;
	}

	//TODO() check if the above ZeroPage,X note applys to ZeroPage,y too
	void Cpu::storeRegisterZeroPageY(uint8_t dest, uint8_t& src) {
		storeRegister((uint16_t) (0x00FF & (dest + y)), src);
		counter.pc += 2;
	}

	void Cpu::storeRegisterAbsolute(uint16_t dest, uint8_t& src) {
		storeRegister(dest, src);
		counter.pc += 3;
	}

	void Cpu::storeRegisterAbsoluteX(uint16_t dest, uint8_t& src) {
		storeRegister(dest + x, src);
		counter.pc += 3;
	}

	void Cpu::storeRegisterAbsoluteY(uint16_t dest, uint8_t& src) {
		storeRegister(dest + y, src);
		counter.pc += 3;
	}

	void Cpu::storeRegister(uint16_t dest, uint8_t& src) {
		mem.store(dest, src);
	}

	void Cpu::test() {
		accumulator = 1;
		auto TAX = [&]() {transferRegister(x,accumulator);};
		TAX();
		accumulator = 2;
		auto TAY = [&]() {transferRegister(y,accumulator);};
		TAY();
		sp = 3;
		auto TSX = [&]() {transferRegister(x,sp);};
		TSX();
		accumulator = 4;
		auto TXA = [&]() {transferRegister(x,accumulator);};
		TXA();
		x = 5;
		auto TXS = [&]() {sp = x; counter.pc += 2;};
		TXS();  // Deliberately different, http://www.obelisk.demon.co.uk/6502/reference.html#TXS
		y = 6;
		auto TYA = [&]() {transferRegister(accumulator,y);};
		TYA();
		y = 7;
		auto STY_zeroPage = [&](uint8_t dest_addr) {storeRegisterZeroPage(dest_addr, y);};
		STY_zeroPage(0xFF);
		y = 8;
		auto STY_zeroPageX = [&](uint8_t dest_addr) {storeRegisterZeroPageX(dest_addr, y);};
		STY_zeroPageX(0xFF);
		y = 9;
		auto STY_absolute = [&](uint16_t dest_addr) {storeRegisterAbsolute(dest_addr, y);};
		STY_absolute(0xFFCC);
	}
}
