// Class
#include "cpu.h"
// Library
#include <string.h>
#include <stdio.h>

// Project
#include "../mem/mem.h"
// Define

namespace cpu {

	//TODO Do something with the cycle count from the functions
	//TODO Do something with the program counter from the functions

	// Addressing modes
	uint16_t Cpu::Immediate(uint8_t& /*unused*/) {
		return counter.pc++;
	}

	uint16_t Cpu::Absolute(uint8_t& /*unused*/) {
		const uint8_t lo = mem[counter.pc++];
		const uint8_t hi = mem[counter.pc++] << 8;
		return (uint16_t) (lo | hi);
	}

	uint16_t Cpu::AbsoluteXY(uint8_t& offsetRegister) {
		const uint8_t lo = mem[counter.pc++];
		const uint8_t hi = mem[counter.pc++] << 8;
		return ((uint16_t) lo | hi) + offsetRegister;
	}

	uint16_t Cpu::ZeroPage(uint8_t& /*unused*/) {
		return mem[counter.pc++];
	}

	uint16_t Cpu::ZeroPageXY(uint8_t& offsetRegister) {
		return (uint8_t) (mem[counter.pc++] + offsetRegister); // Deliberate cast to drop anything above 0xFF
	}

	uint16_t Cpu::Indirect(uint8_t& /*unused*/) {
		//TODO() stub
		return 0;
	}

	uint16_t Cpu::IndirectXY(uint8_t& offsetRegister) {
		//TODO() stub
		return 0;
	}

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

	inline void Cpu::clearFlag(const uint8_t flag) {
		status &= ~flag;
	}

	inline void Cpu::setFlag(const uint8_t flag) {
		status |= flag;
	}

	inline bool Cpu::getFlag(const uint8_t flag) {
		return !!(status & flag);
	}

	void Cpu::compare(uint16_t& lValueAddress, uint8_t rvalue) {
		uint8_t lValue = mem[lValueAddress];
		if (rvalue >= lValue)
			setFlag(CPU_FLAG_CARRY);
		if (rvalue > lValue)
			setFlag(CPU_FLAG_ZERO_RESULT);
		if (GETBIT((rvalue - lValue), 7))
			setFlag(CPU_FLAG_NEGATIVE_RESULT);
	}

	void Cpu::transferRegister(uint8_t& dest, uint8_t& src, bool setFlags) {
		dest = src;
		if (setFlags) {
			if (!src)
				setFlag(CPU_FLAG_ZERO_RESULT);
			if (GETBIT(src, 7))
				setFlag(CPU_FLAG_NEGATIVE_RESULT);
		}
		counter.pc += 1;
	}

	uint8_t Cpu::ADC(uint16_t& src) {
		//TODO Add with Carry
	}

	void Cpu::AND(uint16_t& src) {
		accumulator &= mem.load(src);
		if (!accumulator)
			setFlag(CPU_FLAG_ZERO_RESULT);
		if (GETBIT(accumulator, 7))
			setFlag(CPU_FLAG_NEGATIVE_RESULT);
	}

	void Cpu::ASL(uint16_t& src) {
		//TODO Arithmetic Shift Left
	}

	void Cpu::BCC(int8_t& offset) {
		if (!getFlag(CPU_FLAG_CARRY))
			counter.pc += offset;
	}

	void Cpu::BCS(int8_t& offset) {
		if (getFlag(CPU_FLAG_CARRY))
			counter.pc += offset;
	}

	void Cpu::BEQ(int8_t& offset) {
		if (getFlag(CPU_FLAG_ZERO_RESULT))
			counter.pc += offset;
	}

	void Cpu::BIT(uint16_t& src) {
		uint8_t testValue = mem[src];
		if (!(testValue & accumulator))
			setFlag(CPU_FLAG_ZERO_RESULT);
		if (GETBIT(src, 6))
			setFlag(CPU_FLAG_OVERFLOW);
		if (GETBIT(src, 7))
			setFlag(CPU_FLAG_NEGATIVE_RESULT);
	}

	void Cpu::BMI(int8_t& offset) {
		if (getFlag(CPU_FLAG_NEGATIVE_RESULT))
			counter.pc += offset;
	}

	void Cpu::BNE(int8_t& offset) {
		if (!getFlag(CPU_FLAG_ZERO_RESULT))
			counter.pc += offset;
	}

	void Cpu::BPL(int8_t& offset) {
		if (!getFlag(CPU_FLAG_NEGATIVE_RESULT))
			counter.pc += offset;
	}

	void Cpu::BRK() {
		//TODO Force Interrupt
	}

	void Cpu::BVC(int8_t& offset) {
		if (!getFlag(CPU_FLAG_OVERFLOW))
			counter.pc += offset;
	}

	void Cpu::BVS(int8_t& offset) {
		if (getFlag(CPU_FLAG_OVERFLOW))
			counter.pc += offset;
	}

	void Cpu::CLC() {
		clearFlag(CPU_FLAG_CARRY);
	}

	void Cpu::CLD() {
		clearFlag(CPU_FLAG_DECIMAL);
	}

	void Cpu::CLI() {
		clearFlag(CPU_FLAG_INTERRUPT_DISABLE);
	}

	void Cpu::CLV() {
		clearFlag(CPU_FLAG_OVERFLOW);
	}

	void Cpu::CMP(uint16_t& src) {
		compare(src, accumulator);
	}

	void Cpu::CPX(uint16_t& src) {
		compare(src, x);
	}

	void Cpu::CPY(uint16_t& src) {
		compare(src, y);
	}

	//////////

	void Cpu::SEC() {
		setFlag(CPU_FLAG_CARRY);
	}

	void Cpu::SED() {
		setFlag(CPU_FLAG_DECIMAL);
	}

	void Cpu::SEI() {
		setFlag(CPU_FLAG_INTERRUPT_DISABLE);
	}

	void Cpu::STA(uint16_t dest) {
		mem[dest] = accumulator;
	}

	void Cpu::STX(uint16_t dest) {
		mem[dest] = x;
	}

	void Cpu::STY(uint16_t dest) {
		mem[dest] = y;
	}

	void Cpu::TAX() {
		transferRegister(x, accumulator, true);
	}

	void Cpu::TAY() {
		transferRegister(y, accumulator, true);
	}

	void Cpu::TSX() {
		transferRegister(x, sp, true);
	}

	void Cpu::TXA() {
		// Deliberately doesn't set the flags
		transferRegister(accumulator, x, false);
	}

	void Cpu::TXS() {
		transferRegister(sp, x, true);
	}

	void Cpu::TYA() {
		transferRegister(accumulator, y, true);
	}
}
