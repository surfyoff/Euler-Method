#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

class Input
{
private:

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Rect rect;
	SDL_Rect textRect;
	int width, height;
	SDL_Texture* textTexture;
	string inputText;
	bool isActive;
	bool isFilled;

	void renderText();

public:

	Input(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h);
	
	void handleEvent(SDL_Event &e);
	void render();
	

	string getInputText();

	double getDouble();
	int getInt();
	bool getState();
	bool Full();

	~Input();

};