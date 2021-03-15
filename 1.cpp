#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char* argv[]) {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK)
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button)
            }
        }
    }
}
