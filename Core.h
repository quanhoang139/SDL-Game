#pragma once

#ifndef _CORE_H_
#define _CORE_H_

#include "Texture.h"
#include<random>
#include<queue>
#include "Partical.h"
#include <iostream>


using namespace std;

class Core {
    private:
        Texture gameTexture;
        int id = -1;
        int a[10][10];
        bool canMove = false;
        queue<int> q, erasedBlockID;
        int color[10][10], catColor;
        Partical* partical[20];
        int score = 0, level = 1, target = 1000, more = 1500, scount = 2, highscore = 0;
    public:
        void init(SDL_Renderer* &renderer);

        void renderTexture(SDL_Renderer* renderer);
        void handlingEvent(SDL_Event &e);
        void solve();
        void solveTexture(SDL_Renderer* renderer);
        void newLevel();
};

#endif // _CORE_H_
