#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include "main.h"
#include "Input.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow(
		"Euler Method",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		0
	);

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	bool done = false;
	while (!done)
	{
		done = processEvent(window);
	}

	return EXIT_SUCCESS;
}

bool processEvent(SDL_Window* window)
{
	bool done = false;
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			if (window)
			{
				done = true;
			}
			break;
		case SDL_QUIT:
			done = 1;
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		}
	}

	return done;
}