//============================================================================
// Name        : miNES.cpp
// Author      : Jake Clarke; Nick Sparks;
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================


#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "version.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <SDL.h>



#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 460
#define APP_NAME "miNES"

#define DEFAULT_ROM "game.rom"

static std::string rom = DEFAULT_ROM;

static int windowHeight = DEFAULT_WINDOW_HEIGHT, windowWidth = DEFAULT_WINDOW_WIDTH;

void printUsage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "--help: prints the help and the usage" << std::endl;
	std::cout << "--rom: set the rom to load. (defaults to: " DEFAULT_ROM ")" << std::endl;
	std::cout << "--height: sets the window height" << std::endl;
	std::cout << "--width: sets the window width" << std::endl;
}

void printHelp() {
	std::cout << APP_NAME " - version: " GIT_REV << std::endl << std::endl;
	std::cout << "a crappy emulator. Very much a work in progress." << std::endl << std::endl;
	printUsage();
}

bool Running;

void handleSDLEvents(SDL_Event * Event) {
	switch(Event->type) {
		case SDL_QUIT:
			Running = false;
			std::cout << "Exit requested" << std::endl;
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
				std::cerr << "expected a rom to load." << std::endl;
				return EXIT_FAILURE;
			}
		} else if (strcmp(argv[i], "--width") == 0) {
			if (argc + 1 < argc) {
				windowWidth = atoi(argv[i++]);
			} else {
				std::cerr << "expected screen width." << std::endl;
				return EXIT_FAILURE;
			}
		} else if (strcmp(argv[i], "--height") == 0) {
			if (argc + 1 < argc) {
				windowHeight = atoi(argv[i++]);
			} else {
				std::cerr << "expected screen height." << std::endl;
				return EXIT_FAILURE;
			}
		} else {
			std::cerr << "parameter "  << argv[i] << " is not expected." << std::endl;
			printUsage();
			return EXIT_SUCCESS;
		}
	}

	auto cart = cart::loadCart(rom);
	if (!cart) {
		std::cerr << "failed to read rom: " << rom << std::endl;
		return EXIT_FAILURE;
	}
	auto bank = std::unique_ptr<mem::Mem>(new mem::Mem(cart));
	auto maincpu = std::unique_ptr<cpu::Cpu>(new cpu::Cpu(bank.get()));
	auto mainppu = std::unique_ptr<ppu::Ppu>(new ppu::Ppu(bank.get()));


	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window;

	{
		std::string title = APP_NAME" - " + rom;
	    window = SDL_CreateWindow(
	        title.c_str(),                             // window title
	        SDL_WINDOWPOS_UNDEFINED,           // initial x position
	        SDL_WINDOWPOS_UNDEFINED,           // initial y position
	        windowWidth,                      // width, in pixels
	        windowHeight,                      // height, in pixels
	        0
	    );
	}


    if (window == nullptr) {
        std::cerr << "Could not create window: %s\n"  << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == nullptr){
		std::cerr << "Failed to create hardware renderer: SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		std::cerr << "Falling back to software rendering..." << std::endl;

		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		if (render == nullptr){ 
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			std::cerr << "Failed to create any renderer." << std::endl;
			return EXIT_FAILURE;
		}
	}

	SDL_RenderClear(render);
	SDL_RenderPresent(render);

	Running = true;
	SDL_Event Event;
	while (true) {
		while(SDL_PollEvent(&Event)) {
			handleSDLEvents(&Event);
        }
        if (!Running) {
        	break;
        }

        // 3:1 tick ratio.
        maincpu->tick();

        mainppu->tick();
        mainppu->tick();
        mainppu->tick();
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}
