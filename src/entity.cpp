#include "entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 108;
    currentFrame.h = 108;    
}




SDL_Texture* Entity::getTex() {
    return tex;

}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}
