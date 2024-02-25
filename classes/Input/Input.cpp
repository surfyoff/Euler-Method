#include "Input.h"

Input::Input(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h) : renderer(renderer), font(font), rect({ x, y, w, h }), isActive(false) 
{
    textTexture = nullptr;
}

void Input::handleEvent(SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h)
        {
            isActive = true;
        }
        else
        {
            isActive = false;
        }
        break;
    case SDL_KEYDOWN:
        if (isActive)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                if (!inputText.empty()) inputText.pop_back();
                
            case SDLK_RETURN:
                cout << "Input Text: " << inputText << endl;
            default:
                inputText += e.key.keysym.sym;
            }
            renderText();
        }
    }
}

void Input::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 78, 154, 6, 255);
    SDL_RenderDrawRect(renderer, &rect);

    if (isActive) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    }
    SDL_RenderFillRect(renderer, &rect);

    if (!inputText.empty() && textTexture != nullptr) {
        SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    }
}

string Input::getInputText()
{
    return inputText;
}

void Input::renderText() 
{
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), { 255, 255, 255, 255 });
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

void Input::terminate()
{
    SDL_DestroyTexture(textTexture);
}

double Input::getDouble()
{
    return stod(inputText);
}

int Input::getInt()
{
    return stoi(inputText);
}