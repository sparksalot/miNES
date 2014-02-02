//============================================================================
// Name        : miNES.cpp
// Author      : Jake Clarke; Nick Sparks;
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "mem/mem.h"

#define WINDOW_WIDTH 640
#define WINDOW_HIGHT 460
#define TITLE "miNES"


cpu::Cpu * mainCpu = NULL;
ppu::Ppu * mainPpu = NULL;
mem::Mem * bank = NULL;



bool Running;

void handleSDLEvents(SDL_Event * Event) {
	switch(Event->type) {
		case SDL_QUIT:
			Running = false;
		break;
	}
}

int main(void) {
	mainCpu = new cpu::Cpu();
	bank = mainCpu->getMem();
	mainPpu = new ppu::Ppu(bank->getBank());

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError());
        return 1;
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

    if (window == NULL)
    {
    	fprintf(stderr, "SDL_CreateWindow Error:  %s\n", SDL_GetError());
    	return 1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL){
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 1;
	}

    SDL_Event Event;

    Running = true;

    SDL_RenderClear(render);

	while (Running) {
		while(SDL_PollEvent(&Event)) {
			handleSDLEvents(&Event);
        }
        mainCpu->tick();
        mainPpu->tick();
        mainPpu->tick();
        mainPpu->tick();
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}
