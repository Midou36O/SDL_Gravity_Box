#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class MusicPlayer {
    public:
        MusicPlayer(const char* p_filepath);
        MusicPlayer* loadMusic(const char* p_filepath);
        void playMusic();
        void initMixer();
        void initMusic();

    private:
        Mix_Music* music;
};