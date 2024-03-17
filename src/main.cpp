#include <iostream>
#include <string>
#include <cmath>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "main.h"
#include "Input.h"

using namespace std;



int main(int argc, char *argv[])
{
	SDL_Window* window;


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

	font = TTF_OpenFont("res/courier.ttf", 14);

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
		[0] = initSpeed
		[1] = A (Initial acceleration)
		[2] = B (Time caracteristic)
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

		if (is_ready(data) && check_modif(data))
		{
			initSpeed = data[0].getDouble();			
			A = data[1].getDouble();
			B = 1 / data[2].getDouble();
			timeStep = data[3].getDouble();
			n = data[4].getInt();


			if (!done_processing && start)
			{
				process_data(data);
			}
		}
		else
		{
			start = false;
		}


		do_render(renderer, data);
	}

	SDL_StopTextInput();

	if (GUItex)
	{
		SDL_DestroyTexture(GUItex);
		GUItex = nullptr;
	}
	if (x)
	{
		SDL_DestroyTexture(x);
		x = nullptr;
	}
	if (y)
	{
		SDL_DestroyTexture(y);
		y = nullptr;
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
				done = true;
			break;
			case SDLK_p:
				for (int i = 0; i < 5; i++)
				{
					cout << "Input text number " << i + 1 << ": " << data[i].getDouble() << endl;
				}
			break;
			case SDLK_n:
				if (A != 1e10 && B != 1e10 && initSpeed != 1e10 && timeStep != 1e10 && n != 0)
				{
					cout << "Initial Acceleration: " << A << endl;
					cout << "Caracteristic time: " << B << endl;
					cout << "Initial Speed: " << initSpeed << endl;
					cout << "Time Step: " << timeStep << endl;
					cout << "Velocity power: " << n << endl;
				}
			break;
			case SDLK_r:
				if (is_ready(data) && start)
				{
					render = true;
				}
			break;
			case SDLK_s:
				render = false;
			break;
			case SDLK_UP:
				y_sens += 20;
				cout << "Y sensibility: " << 30 / y_sens << " m/s" << endl;

			break;
			case SDLK_DOWN:
				y_sens -= 20;
				cout << "Y sensibility: " << 30 / y_sens << " m/s" << endl;

			break;
			case SDLK_b:
				if (!start)
				{
					start = true;
					done_processing = false;
				}
				break;
			default:
				break;
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

void do_render(SDL_Renderer* renderer, Input data[5])
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

	if (done_processing)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		graph[0] = { 10, 469 };
		for (int i = 0; i < 103; i++)
		{
			graph[i + 1].x = 10 + x_sens * i;
			graph[i + 1].y = HEIGHT - 11 - Vel[i] * y_sens;
		}

		if (render)
		{
			SDL_RenderDrawLinesF(renderer, graph, 104);


			SDL_Color green = { 78, 154, 6, 255 };

			string x_setting = to_string((float)timeStep);
			x_setting.append(" s");

			string y_setting = to_string((float)(30 / y_sens));
			y_setting.append(" m/s");

			SDL_Surface* surface = TTF_RenderText_Solid(font, x_setting.c_str(), green);
			if (surface)
			{
				x = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_QueryTexture(x, nullptr, nullptr, &x_text_width, &x_text_height);

				SDL_Rect x_rect = { 108, 128, x_text_width, x_text_height };
				SDL_RenderCopy(renderer, x, nullptr, &x_rect);

				SDL_DestroyTexture(x);
			}
			SDL_FreeSurface(surface);
			surface = TTF_RenderText_Solid(font, y_setting.c_str(), green);
			if (surface)
			{
				y = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_QueryTexture(y, nullptr, nullptr, &y_text_width, &y_text_height);

				SDL_Rect y_rect = { 108, 144, y_text_width, y_text_height };
				SDL_RenderCopy(renderer, y, nullptr, &y_rect);

				SDL_DestroyTexture(y);
			}
			SDL_FreeSurface(surface);
			surface = nullptr;
		}
	}

	SDL_RenderPresent(renderer);
}



void process_data(Input data[5])
{
	currentSpeed = initSpeed;
	currentAcceleration = A - B * pow(initSpeed, n);


	for (int i = 0; i < 103; i++)
	{
		// Calculate the next Speed and Acceleration
		nextSpeed = currentSpeed + currentAcceleration * timeStep;
		nextAcceleration = A - B * pow(nextSpeed, n);

		Vel[i] = currentSpeed;

		cout << "Speed " << i << ": " << currentSpeed << endl;
		cout << "Acceleration " << i << ": " << currentAcceleration << endl << endl;

		// Update Speed and Acceleration values for the next iteration
		currentSpeed = nextSpeed;
		currentAcceleration = nextAcceleration;
	}

	cout << endl;

	done_processing = true;
}

bool is_ready(Input data[5])
{
	for (int i = 0; i < 5; i++)
	{
		if (!data[i].Full())
		{
			return false;
		}
	}

	return true;
}

bool check_modif(Input data[5])
{
	for (int i = 0; i < 5; i++)
	{
		if (data[i].isModified())
		{
			return false;
		}
	}

	return true;
}