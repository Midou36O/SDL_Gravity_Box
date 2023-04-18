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
int MusicPlayer::loadMusic(const char* p_filepath) {

    Mix_Music* music = NULL;
    music = Mix_LoadMUS(p_filepath);

    if (music == NULL) {
        std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
        return 1;
    }
    Mix_PlayMusic(music, -1);
    return 0;
}

void MusicPlayer::playMusic() {
    if (Mix_PlayingMusic() == 0) {
        std::cerr << "Music is not playing!" << std::endl;
    }
}

void MusicPlayer::initMixer() {
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_Mixer couldnt init. Err: " <<  Mix_GetError() << std::endl;
	}
}
