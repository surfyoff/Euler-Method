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

	TTF_Font *font = TTF_OpenFont("res/courier.ttf", 20);

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

	SDL_Event e = {};

	Input data[5] = {
		Input(renderer, font, 536, 80, 98, 18),
		Input(renderer, font, 536, 107, 98, 18),
		Input(renderer, font, 536, 134, 98, 18),
		Input(renderer, font, 536, 161, 98, 18),
		Input(renderer, font, 536, 188, 98, 18)
	};

	SDL_StartTextInput();
	
	bool done = false;
	while (!done)
	{
		done = processEvent(window, e, data);

		do_render(renderer, font, data);
	}

	SDL_StopTextInput();

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
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				done = 1;
			}
			else if (e.key.keysym.sym == SDLK_p)
			{
				for (int i = 0; i < 5; i++)
				{
					cout << "Input text number " << i << ": " << data[i].getInputText() << endl;
				}
			}
		break;
		}
		
		for (int i = 0; i < 5; i++)
		{
			data[i].handleEvent(e);
		}
	}

	return done;
}

void do_render(SDL_Renderer* renderer, TTF_Font* font, Input data[5])
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect GUIrect = { 0, 0, WIDTH, HEIGHT };

	SDL_RenderCopy(renderer, GUItex, NULL, &GUIrect);

	for (int i = 0; i < 5; i++)
	{
		if (data[i].getState() || data[i].Full())
		{
			data[i].render();
		}
	}

	SDL_RenderPresent(renderer);
}

