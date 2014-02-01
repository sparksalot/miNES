//============================================================================
// Name        : miNES.cpp
// Author      : Jake Clarke; Nick Sparks;
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "mem/mem.h"

cpu::Cpu * mainCpu = NULL;
ppu::Ppu * mainPpu = NULL;
mem::Mem * bank = NULL;

int main(void) {
	mainCpu = new cpu::Cpu();
	bank = mainCpu->getMem();
	mainPpu = new ppu::Ppu(bank->getBank());

	while (true) {
		mainCpu->tick();
	}

	return EXIT_SUCCESS;
}
