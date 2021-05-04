#pragma once

#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL.h>
#include <SDL_mixer.h>

class Sound {
    private:
        bool musicVol;
        bool effectVol;

        Mix_Music* gameBG = nullptr;
        Mix_Chunk* effect[17];
    public:
        static const int CLICK_CAT = 0;
        static const int GAME_OVER = 15;
        static const int STAGE_CLEAR = 16;
        Sound();
        ~Sound();
        void load();
        void playEffect(int id);
        void changeMusicVol();
        void changeEffectVol();
        bool getMusicVol() const;
        bool getEffectVol() const;
};

#endif // _SOUND_
