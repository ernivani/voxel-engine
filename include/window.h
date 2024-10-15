#pragma once

#include <SDL2/SDL.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};