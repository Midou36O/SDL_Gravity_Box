#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class MusicPlayer {
    public:
        MusicPlayer(const char* p_filepath);
        Mix_Music* loadMusic(const char* p_filepath);
        void playMusic();
        void initMusic();

    private:
        Mix_Music* music;
};