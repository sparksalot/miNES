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

cpu::Cpu maincpu;

int main(void) {

	while(true) {
		maincpu.tick();
	}

	return EXIT_SUCCESS;
}
