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
        SDL_Texture* background;
        SDL_Texture* catTexture[5];
        SDL_Texture* menuBG;
        SDL_Texture* nxlvBoard;
        SDL_Texture* recordList;
        SDL_Texture* gameOver;
        SDL_Texture* stageClear;
        TTF_Font *font = nullptr;

        SDL_Texture* loadImage(SDL_Renderer* renderer, const std::string imgPath);
        void renderText(SDL_Renderer* renderer, std::string text, SDL_Color color, int posX, int posY);
    public:
        Texture();
        ~Texture();

        void loadMedia(SDL_Renderer* renderer);
        void renderMedia(SDL_Renderer* renderer, int a[10][10], const int score, const int level, const int target, const int highscore);
        void renderMenu(SDL_Renderer* renderer);
        void renderNXLVBoard(SDL_Renderer* renderer, const int score, const int level, const int target);
        void renderRecordList(SDL_Renderer* renderer, const std::pair<int, int> highscore[5]);
        void renderGameOver(SDL_Renderer* renderer, const int score, const int level, const int target, const int highscore);
        void renderStageClear(SDL_Renderer* renderer, int a[10][10], const int score, const int level, const int target, const int highscore);
        SDL_Texture* getCatTexture(int id);
};

#endif
