#include "Texture.h"

using namespace std;

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
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("catyelow.png");
    catTexture[0] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageSurface = IMG_Load("catgreen.png");
    catTexture[1] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageSurface = IMG_Load("catblue.png");
    catTexture[2] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageSurface = IMG_Load("catred.png");
    catTexture[3] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageSurface = IMG_Load("catpurple.png");
    catTexture[4] = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    font = TTF_OpenFont("x.ttf", 20);
}

void Texture::renderMedia(SDL_Renderer* renderer, int a[10][10], const int &score, const int &level, const int &target, const int &highscore)
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

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, ("High Score : " + to_string(highscore)).c_str(), {0, 255, 255, 255});
    dsRect = {0, 0, textSurface->w, textSurface->h};
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    textSurface = TTF_RenderText_Blended(font, ("Level : " + to_string(level)).c_str(), {0, 255, 255, 255});
    dsRect = {0, 30, textSurface->w, textSurface->h};
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    textSurface = TTF_RenderText_Blended(font, ("Target : " + to_string(target)).c_str(), {0, 255, 255, 255});
    dsRect = {120, 30, textSurface->w, textSurface->h};
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {0, 255, 255, 255});
    dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* Texture :: getCatTexture(int id)
{
    return catTexture[id];
}
