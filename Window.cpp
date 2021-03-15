#include "Window.h"
#include"engine.h"
#include <iostream>
#include<time.h>
#include<random>

Window::Window() {
    window = nullptr;
    renderer = nullptr;
}

Window::~Window() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << SDL_GetError() << std::endl;
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << SDL_GetError() << std::endl;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == nullptr)
            {
                std::cout<<SDL_GetError()<<std::endl;
            }

        }
    }
}

void Window::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::run() {
    SDL_Event e;
    bool quit = false;

    gamePlay.init(renderer);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_MOUSEBUTTONDOWN) gamePlay.handlingEvent(e);
        }
        gamePlay.solve();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        gamePlay.renderTexture(renderer);
        SDL_RenderPresent(renderer);
    }
}
