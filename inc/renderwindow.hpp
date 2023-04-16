#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath); 
        void cleanUp();
        void GetWinPos(int *WinPosX, int *WinPosY);
        void clear();
        void render(Entity &p_entity, int Pos_h);
        void display();
 
    private:

        SDL_Window* window;
        SDL_Renderer* renderer;
};