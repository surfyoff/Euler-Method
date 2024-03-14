#pragma once

#include "Input.h"

#define WIDTH 640
#define HEIGHT 480


SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;


double A = 1e10, B = 1e10, initSpeed = 1e10, timeStep = 1e10;
int n = 0;

double currentAcceleration, currentSpeed;
double nextAcceleration, nextSpeed;

bool done_processing = false;
bool render = false;

double Vel[103] = { 0 };

SDL_Texture* GUItex = nullptr;
SDL_FPoint graph[104];

SDL_Texture* x = nullptr, * y = nullptr;
int x_text_width = 0, x_text_height = 0;
int y_text_width = 0, y_text_height = 0;
double x_sens = 6, y_sens = 300;

bool start = false;

bool processEvent(SDL_Window* window, SDL_Event &e, Input data[5]);

void do_render(SDL_Renderer* renderer, Input data[5]);

void process_data(Input data[5]);

bool is_ready(Input data[5]);

bool check_modif(Input data[5]);