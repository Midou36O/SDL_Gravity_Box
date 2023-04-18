#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class MusicPlayer {
    public:
        //MusicPlayer(const char* p_filepath);
        Mix_Chunk* loadMusic(const char* p_filepath);
        void playMusic();
        void openAudio();
        void closeAudio();
        void freeMusic();
    private:
        Mix_Chunk* music;
};