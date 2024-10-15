#include "window.h"
#include <iostream>

Window::Window(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
    }

    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (!window_) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
    }
}

Window::~Window() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

SDL_Renderer* Window::getRenderer() const {
    return renderer_;
}