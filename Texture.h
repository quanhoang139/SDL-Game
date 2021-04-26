#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
    private:
        SDL_Surface* imageSurface;
        SDL_Texture* background;
        SDL_Texture* catTexture[5];
        TTF_Font *font = nullptr;

    public:
        Texture();
        ~Texture();

        void loadMedia(SDL_Renderer* renderer);

        void renderMedia(SDL_Renderer* renderer, int a[10][10],
                         const int &score, const int &level, const int &target, const int &highscore);

        SDL_Texture* getCatTexture(int id);
};

#endif
