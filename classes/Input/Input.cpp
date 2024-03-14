#include "Input.h"

Input::Input(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h) :
    renderer(renderer),
    font(font), rect({ x, y, w, h }),
    isActive(false),
    textRect({ x, y, 0, h }),
    isFilled(false),
    modified(false)
{
    textTexture = nullptr;
    width = 0;
    height = 0;

}

void Input::handleEvent(SDL_Event &e)
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
                    if (!inputText.empty())
                    {
                        inputText.pop_back();
                        modified = true;
                        
                    }
                    break;
                case SDLK_RETURN:
                    isActive = false;
                    break;
                }
            }
        break;
        case SDL_TEXTINPUT:
            if (isActive)
            {
                inputText += e.text.text;
                renderText();
                modified = true;
            }
        break;
        default:
            modified = false;
        break;
    }
}

void Input::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 78, 154, 6, 255);
    SDL_RenderDrawRect(renderer, &rect);

    if (isActive) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 78, 154, 6, 255);

    if (!inputText.empty() && textTexture != nullptr) {
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        isFilled = true;
    }
    else if (inputText.empty())
    {
        isFilled = false;
    }
}

string Input::getInputText()
{
    return inputText;
}

void Input::renderText() 
{
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, inputText.c_str(), { 255, 255, 255, 255 }, 98);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;

    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

Input::~Input()
{
    SDL_DestroyTexture(textTexture);
}

bool Input::Full()
{
    return isFilled;
}

double Input::getDouble()
{
    return stod(inputText);
}

int Input::getInt()
{
    return stoi(inputText);
}

bool Input::getState()
{
    return isActive;
}

bool Input::isModified()
{
    return modified;
}
