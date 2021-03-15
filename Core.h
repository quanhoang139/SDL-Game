#pragma once

#ifndef _CORE_H_
#define _CORE_H_

#include "Texture.h"
#include<random>
#include<queue>

using namespace std;

class Core {
    private:
        Texture gameTexture;

        int a[10][10];
        bool canMove = false;
        queue<int> q;
        int color[10][10];

    public:
        void init(SDL_Renderer* &renderer) {
            gameTexture.loadMedia(renderer);

            for(int i = 0; i < 10; ++i)
                for(int j = 0; j < 10; ++j) a[i][j] = rand() % 5;
        }


        void renderTexture(SDL_Renderer* renderer) {
            gameTexture.renderMedia(renderer, a);
        }
        void handlingEvent(SDL_Event &e);
        void solve();
};

#endif // _CORE_H_
