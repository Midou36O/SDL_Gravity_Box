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

Mix_Music* MusicPlayer::loadMusic(const char* p_filepath) {
    Mix_Music* music = NULL;
    music = Mix_LoadMUS(p_filepath);

    if (music == NULL) {
        std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
    }
    return music;
}

void MusicPlayer::playMusic() {
    if (Mix_PlayingMusic() == 0) {
        std::cerr << "Music is not playing!" << std::endl;
    }
}
