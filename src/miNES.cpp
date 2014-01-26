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
#include <SDL.h>
#include <iostream>

#include "version.h"

#define WINDOW_WIDTH 640
#define WINDOW_HIGHT 460
#define TITLE "miNES"

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

bool Running;

void handleSDLEvents(SDL_Event * Event) {
	switch(Event->type) {
		case SDL_QUIT:
			Running = false;
		break;
	}
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


	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window; 

    window = SDL_CreateWindow(
        TITLE,                             // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        WINDOW_WIDTH,                      // width, in pixels
        WINDOW_HIGHT,                      // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL){
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_RenderClear(render);

	SDL_Event Event;
	while (Running) {
		while(SDL_PollEvent(&Event)) {
			handleSDLEvents(&Event);
        }
        maincpu->tick();
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}
