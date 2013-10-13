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

cpu::Cpu cpu;


int main(void) {

	while(true) {
		cpu.tick();
	}

	return EXIT_SUCCESS;
}
