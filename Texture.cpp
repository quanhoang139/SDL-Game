#include "Texture.h"
#include <SDL_mixer.h>

using namespace std;

Texture::Texture()
{
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

    TTF_CloseFont(font);
}

SDL_Texture* Texture::loadImage(SDL_Renderer* renderer, const std::string imgPath) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void Texture::renderText(SDL_Renderer* renderer, std::string text, SDL_Color color, int posX, int posY) {
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Rect dsRect = {posX, posY, textSurface->w, textSurface->h};
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Texture::loadMedia(SDL_Renderer* renderer)
{
    background = loadImage(renderer, "asset/Image/city2.jpg");
    catTexture[0] = loadImage(renderer, "asset/Image/catyelow.png");
    catTexture[1] = loadImage(renderer, "asset/Image/catgreen.png");
    catTexture[2] = loadImage(renderer, "asset/Image/catblue.png");
    catTexture[3] = loadImage(renderer, "asset/Image/catred.png");
    catTexture[4] = loadImage(renderer, "asset/Image/catpurple.png");
    menuBG = loadImage(renderer, "asset/Image/menu.png");
    nxlvBoard = loadImage(renderer, "asset/Image/next level board.png");
    recordList = loadImage(renderer, "asset/Image/record list.png");
    gameOver = loadImage(renderer, "asset/Image/game over.png");
    stageClear = loadImage(renderer, "asset/Image/stage clear.png");
}

void Texture::renderMedia(SDL_Renderer* renderer, int a[10][10], const int score, const int level, const int target, const int highscore)
{
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect dsRect;
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            dsRect = {i * 40, j * 40 + 200, 40, 40};
            if (a[j][i] == -1) continue;
            SDL_RenderCopy(renderer, catTexture[a[j][i]], nullptr, &dsRect);
        }
    }
    font = TTF_OpenFont("x.ttf", 20);
    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
    dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void Texture::renderMenu(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, menuBG, nullptr, nullptr);
}

void Texture::renderNXLVBoard(SDL_Renderer* renderer, const int score, const int level, const int target) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect dsRect = {200 - 141, 333 - 175, 282, 350};
    SDL_RenderCopy(renderer, nxlvBoard, nullptr, &dsRect);
    font = TTF_OpenFont("x.ttf", 20);
    renderText(renderer, to_string(level), {255, 255, 255, 255}, 190, 337);
    renderText(renderer, to_string(target), {255, 255, 255, 255}, 190, 375);
    TTF_CloseFont(font);
    font = TTF_OpenFont("x.ttf", 30);
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, to_string(score).c_str(), {255, 255, 255, 255});
    dsRect = {200 - textSurface->w / 2, 250, textSurface->w, textSurface->h};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void Texture::renderRecordList(SDL_Renderer* renderer, const std::pair<int, int> hightscore[5]) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect dsRect = {200 - 190, 100, 380, 476};
    SDL_RenderCopy(renderer, recordList, nullptr, &dsRect);
    font = TTF_OpenFont("x.ttf", 30);
    renderText(renderer, "Level " + to_string(hightscore[0].second) + ": " + to_string(hightscore[0].first), {255, 126, 0, 255}, 110, 215);
    renderText(renderer, "Level " + to_string(hightscore[1].second) + ": " + to_string(hightscore[1].first), {216, 255, 0, 255}, 110, 295);
    renderText(renderer, "Level " + to_string(hightscore[2].second) + ": " + to_string(hightscore[2].first), {48, 255, 13, 255}, 110, 372);
    renderText(renderer, "Level " + to_string(hightscore[3].second) + ": " + to_string(hightscore[3].first), {255, 255, 255, 255}, 110, 445);
    renderText(renderer, "Level " + to_string(hightscore[4].second) + ": " + to_string(hightscore[4].first), {255, 255, 255, 255}, 110, 523);
    TTF_CloseFont(font);
}

void Texture::renderGameOver(SDL_Renderer* renderer, const int score, const int level, const int target, const int highscore) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    font = TTF_OpenFont("x.ttf", 20);
    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
    SDL_Rect dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    static int scale = 0;
    ++scale;
    if (Mix_Playing(2) == 0) scale = 0;
    if (scale > 50) scale = 50;
    dsRect.w = 5 * scale;
    dsRect.h = 1 * scale;
    dsRect.x = 200 - dsRect.w / 2;
    dsRect.y = 333 - dsRect.h / 2;
    SDL_RenderCopy(renderer, gameOver, nullptr, &dsRect);
}

void Texture::renderStageClear(SDL_Renderer* renderer, int a[10][10], const int score, const int level, const int target, const int highscore) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect dsRect;
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            dsRect = {i * 40, j * 40 + 200, 40, 40};
            if (a[j][i] == -1) continue;
            SDL_RenderCopy(renderer, catTexture[a[j][i]], nullptr, &dsRect);
        }
    }
    font = TTF_OpenFont("x.ttf", 20);
    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
    dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    static int scale = 0;
    scale += 2;
    if (Mix_Playing(2) == 0) scale = 0;
    if (scale > 130) scale = 130;
    dsRect.w = 2 * scale;
    dsRect.h = 1 * scale;
    dsRect.x = 200 - dsRect.w / 2;
    dsRect.y = 333 - dsRect.h / 2;
    SDL_RenderCopy(renderer, stageClear, nullptr, &dsRect);
}

SDL_Texture* Texture :: getCatTexture(int id)
{
    return catTexture[id];
}
