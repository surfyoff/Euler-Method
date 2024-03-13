#pragma once

#include "Input.h"

#define WIDTH 640
#define HEIGHT 480

bool processEvent(SDL_Window* window, SDL_Event &e, Input data[5]);

void do_render(SDL_Renderer* renderer, TTF_Font* font, Input data[5]);

void process_data(Input data[5]);

bool is_ready(Input data[5]);

bool check_modif(Input data[5]);