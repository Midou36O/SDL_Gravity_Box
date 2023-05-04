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


void MusicPlayer::initMusic() {
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS );
}

void MusicPlayer::openAudio() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
}

Mix_Music* MusicPlayer::loadMusic(const char* p_filepath) {
    // Good practice to set the pointer to NULL.
    Mix_Music* music = NULL;
    music = Mix_LoadMUS(p_filepath);

    if (music == NULL) {
        std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
    }
    return music;
}


void MusicPlayer::closeAudio() {
    Mix_HaltMusic();
    Mix_CloseAudio();
    Mix_Quit();
}

void MusicPlayer::playMusic() {
    //Mix_PlayChannel(-1, music, 0);
    //Mix_PlayMusic(-1, music);
}

void MusicPlayer::freeMusic() {
    Mix_FreeMusic(music);
}