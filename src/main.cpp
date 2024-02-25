#include <iostream>
#include <string>
#include <vector>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "main.h"
#include "Input.h"

using namespace std;

double A, B, initSpeed, timeStep;
int n;

SDL_Texture* GUItex = NULL;

int main(int argc, char *argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	if (IMG_Init(IMG_INIT_PNG) != 2)
	{
		cout << "Error: " << IMG_GetError() << endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	if (TTF_Init() != 0)
	{
		cout << "Error: " << TTF_GetError() << endl;
		SDL_Quit();
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

	TTF_Font *font = TTF_OpenFont("res/arial.ttf", 28);

	SDL_Surface* surface = IMG_Load("res/GUI.png");
	if (surface == NULL)
	{
		cout << "Error: " << IMG_GetError() << endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}
	GUItex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);


	/*
		[0] = Initial Acceleration
		[1] = Caracteristic Time
		[2] = Initial Speed
		[3] = Time Step
		[4] = Velocity Power
	*/

	Input data[5] = {
		Input(renderer, font, 478, 112, 98, 18),
		Input(renderer, font, 478, 139, 98, 18),
		Input(renderer, font, 478, 166, 98, 18),
		Input(renderer, font, 478, 193, 98, 18),
		Input(renderer, font, 478, 220, 98, 18)
	};


	SDL_Event e;
	bool done = false;
	while (!done)
	{
		done = processEvent(window, e, data);
		
		

		do_render(renderer, font);
		
		
		SDL_RenderPresent(renderer);
	}

	for (int i = 0; i < 5; i++)
	{
		data[i].terminate();
	}

	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();


	return EXIT_SUCCESS;
}

bool processEvent(SDL_Window* window, SDL_Event &e, Input data[5])
{
	bool done = false;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
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
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		
		}
		
		for (int i = 0; i < 5; i++)
		{
			data[i].handleEvent(e);
		}
	}

	return done;
}

void do_render(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect GUIrect = { 0, 0, WIDTH, HEIGHT };

	SDL_RenderCopy(renderer, GUItex, NULL, &GUIrect);

}

