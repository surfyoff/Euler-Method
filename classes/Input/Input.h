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
	SDL_Texture* textTexture;
	string inputText;
	bool isActive;

	void renderText();

public:

	Input(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h);
	
	void handleEvent(SDL_Event& e);
	void render();
	void terminate();

	string getInputText();

	double getDouble();
	int getInt();

};