#include "Partical.h"
#include<random>
#include <iostream>

Partical :: Partical(int id)
{
    int i = id / 40, j = (id) % 40;
    i = i * 40; j = j * 40 + 100;
    posX = (i - rand() % 160) + rand() % 160;
    posY = (j - rand() % 160) + rand() % 160;
    size = rand() % 40;
    frame = rand() % 30;
}

Partical::~Partical() {

}

void Partical :: render(SDL_Renderer* renderer, SDL_Texture* catTexture)
{
    SDL_Rect dsRect = {posX, posY, size, size};
    SDL_RenderCopy(renderer, catTexture, nullptr, &dsRect);
}

bool Partical :: isDead()
{
    if(frame > 0) --frame;
    //std::cout << frame << std::endl;
    if(frame == 0) return true;
    else return false;
}
