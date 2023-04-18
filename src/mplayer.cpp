/**
 * @file mplayer.cpp
 * @author Midou (midou@midou.dev)
 * @brief Simple music player.
 * @version 0.1
 * @date 2023-04-17
 * 
 * 
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "mplayer.hpp"


// TODO: Fix that.
//MusicPlayer::MusicPlayer(const char* p_filepath) {
//
//    Mix_Music* music = NULL;
//    music = Mix_LoadMUS(p_filepath);
//
//    if (music == NULL) {
//        std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
//    }
//    Mix_PlayMusic(music, -1);
//}

Mix_Chunk* MusicPlayer::loadMusic(const char* p_filepath) {
    // Good practice to set the pointer to NULL.
    Mix_Chunk* music = NULL;
    music = Mix_LoadWAV(p_filepath);

    if (music == NULL) {
        std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
    }
    return music;
}

void MusicPlayer::openAudio() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
}

void MusicPlayer::closeAudio() {
    Mix_CloseAudio();
}

void MusicPlayer::playMusic() {
    Mix_PlayChannel(-1, music, 0);
}

void MusicPlayer::freeMusic() {
    Mix_FreeChunk(music);
}