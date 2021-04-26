#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <string>
#include "Core.h"
#include <SDL_ttf.h>

class Window {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Core gamePlay;

        const int SCREEN_WIDTH = 400;
        const int SCREEN_HEIGHT = 600;
        const std::string WINDOW_TITTLE = "Gem Pop";
    public:
        Window();

        ~Window();

        void init();

        void close();

        void run();
};

#endif // _WINDOW_H_
