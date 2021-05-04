#pragma once

#ifndef _CORE_H_
#define _CORE_H_

#include "Texture.h"
#include<random>
#include<queue>
#include "Partical.h"
#include "Button.h"
#include "Sound.h"
#include <iostream>


using namespace std;

class Core {
    private:
        Texture gameTexture;
        Sound gameSound;
        int id = -1, cnt = 0;
        int a[10][10];
        int score;
        int level;
        int target;
        int more;
        int scount;
        std::pair<int, int> highscore[5];
        int curHighScore;
        int curRun;
        bool canMove = false;
        bool continuePre;
        bool gameOver = false;
        bool stageClear = false;
        queue<int> q, erasedBlockID;
        int color[10][10], catColor;
        Partical* partical[16];
        Button button[10];

        void renderMenu(SDL_Renderer* renderer);
        void renderInGame(SDL_Renderer* renderer);
        void renderNXLVBoard(SDL_Renderer* renderer);
        void renderRecordList(SDL_Renderer* renderer);
    public:
        static const int TOTAL_PARTICAL = 16;
        static const int MENU = 0;
        static const int INGAME = 1;
        static const int NXLVBOARD = 2;
        static const int RECORD_LIST = 3;
        void init(SDL_Renderer* &renderer);
        void renderTexture(SDL_Renderer* renderer);
        void handlingEvent(SDL_Event &e);
        void solve();
        void solveTexture(SDL_Renderer* renderer);
        void newLevel();
        void saveData();
};

#endif // _CORE_H_
