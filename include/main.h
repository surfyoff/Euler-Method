#pragma once

#include "Input.h"

#define WIDTH 640
#define HEIGHT 480

bool processEvent(SDL_Window* window, SDL_Event &e, Input data[5]);

void do_render(SDL_Renderer* renderer, TTF_Font* font);

void process_data(Input& data);