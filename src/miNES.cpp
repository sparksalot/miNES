//============================================================================
// Name        : miNES.cpp
// Author      : Jake Clarke; Nick Sparks;
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================


#include "cpu/cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "version.h"

#define DEFAULT_ROM "game.rom"

static std::unique_ptr<cpu::Cpu> maincpu;

static std::string rom = DEFAULT_ROM;

void printUsage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "--help: prints the help and the usage" << std::endl;
	std::cout << "--rom: set the rom to load. (defaults to: "DEFAULT_ROM")" << std::endl;
}

void printHelp() {
	std::cout << "miNES - version: " GIT_REV << std::endl << std::endl;
	std::cout << "a crappy emulator. Very much a work in progress." << std::endl << std::endl;
	printUsage();
}

int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "--help") == 0) {
			printHelp();
			return EXIT_SUCCESS;
		} else if (strcmp(argv[i], "--rom") == 0) {
			if (argc + 1 < argc) {
				rom = argv[i++];
			} else {
				std::cout << "expected a rom to load." << std::endl;
				return EXIT_FAILURE;
			}
		} else {
			std::cout << "parameter "  << argv[i] << " is not expected." << std::endl;
			printUsage();
			return EXIT_SUCCESS;
		}
	}

	maincpu = std::unique_ptr<cpu::Cpu>(new cpu::Cpu());

	while (true) {
		maincpu->tick();
	}

	return EXIT_SUCCESS;
}
