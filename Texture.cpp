#include "Texture.h"
#include<SDL_image.h>

Texture::Texture()
{
    imageSurface = nullptr;
    background = nullptr;
    for(int i = 0; i < 5; ++i) catTexture[i] = nullptr;
}

Texture::~Texture()
{
    if(background != nullptr)
    {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
    for(int i = 0; i < 5; ++i)
    if(catTexture[i] != nullptr)
    {
        SDL_DestroyTexture(catTexture[i]);
        catTexture[i] = nullptr;
    }
}

void Texture::loadMedia(SDL_Renderer* renderer)
{
    imageSurface = IMG_Load("city2.jpg");

    background = SDL_CreateTextureFromSurface(renderer, imageSurface);

    imageSurface = IMG_Load("catyelow.png");
    catTexture[0] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    imageSurface = IMG_Load("catgreen.png");
    catTexture[1] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    imageSurface = IMG_Load("catblue.png");
    catTexture[2] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    imageSurface = IMG_Load("catred.png");
    catTexture[3] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    imageSurface = IMG_Load("catpurple.png");
    catTexture[4] = SDL_CreateTextureFromSurface(renderer, imageSurface);
}

void Texture::renderMedia(SDL_Renderer* renderer, int a[10][10])
{
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect dsRect;
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            dsRect = {i * 40, j * 40 + 100, 40, 40};
            if (a[j][i] == -1) continue;
            SDL_RenderCopy(renderer, catTexture[a[j][i]], nullptr, &dsRect);
        }
    }

}
