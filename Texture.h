#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include<SDL.h>

class Texture
{
    private:
        SDL_Surface* imageSurface;
        SDL_Texture* background;
        SDL_Texture* catTexture[5];
    public:
        Texture();
        ~Texture();

        void loadMedia(SDL_Renderer* renderer);

        void renderMedia(SDL_Renderer* renderer, int a[10][10]);
};

#endif
