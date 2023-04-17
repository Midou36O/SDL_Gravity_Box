#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

/**
 * \brief Represents an Entity in the game.
 * An Entity is any object that can move in the game world,
 * such as a player, a bullet, or an enemy. This class is used to
 * represent any entity in the game. It is used to store information 
 * about the entity, such as its position, texture, and current animation
 * frame. - Copilot 
*/
class Entity {
    
     //p_x : parameter X  || p_y : parameter y

    public:
        Entity(Vector2f p_pos, SDL_Texture* p_tex);
        // void init();
        Vector2f& getPos() {
            return pos;
        } 
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame(); 

    private:
        Vector2f pos; 
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};