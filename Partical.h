#pragma once
#ifndef _PARTICAL_H_
#define _PARTICAL_H_

#include <SDL.h>

class Partical
{
      private:
          int posX, posY;
          int size, frame;
      public:
          Partical(int id);
          ~Partical();
          void render(SDL_Renderer* renderer, SDL_Texture* catTexture);
          bool isDead();


};

#endif
