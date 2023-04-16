#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "entity.hpp"
#include "renderwindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
        :window(NULL), renderer(NULL)
        {
            window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
            if (window == NULL) {
            std::cout << "Window failed to init, ERROR: " << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            
        }


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){

    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL) {
        std::cout << "The texture failed to load!! ERROR: " << SDL_GetError() << std::endl;
    }
    
    return texture;
}
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

// TODO: This line Does nothing since it's "void" (aka doesn't return anything). Make it return something! 
void RenderWindow::GetWinPos(int *WinPosX, int *WinPosY)
{
    SDL_GetWindowPosition(window, WinPosX, WinPosY);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, int Pos_h)
{
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x; 
    src.y = p_entity.getCurrentFrame().y; 
    src.w = p_entity.getCurrentFrame().w; 
    src.h = p_entity.getCurrentFrame().h; 

    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getCurrentFrame().w * Pos_h;
    dst.h = p_entity.getCurrentFrame().h * Pos_h;
    
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
