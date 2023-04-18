#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "entity.hpp"
#include "renderwindow.hpp"

// Creates a new window to render content in it.
// Takes the Title name, w(idth) and h(eight) of the window.
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
        // Create a pointer for window and render and point them to NULL.
        :window(NULL), renderer(NULL)
        {
            window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
            // Fail if the window did not init.
            if (window == NULL) {
            std::cerr << "Window failed to init, ERROR: " << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            
        }

/**
 * Takes the path of the texture to load.
 * 
 * \param p_filePath Path to load the texture.
 * 
*/
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){

    // Declare the texture variable first as NULL.
    // Then Load the texture in the renderer using the given path.
    // Parameters
    // \param renderer Where to render.
    // \param p_filePath Path to load the texture.
    SDL_Texture* texture = NULL;
    // Load the texture in the renderer using the path given.
    texture = IMG_LoadTexture(renderer, p_filePath);

    // Return an error if something goes wrong.
    if (texture == NULL) {
        std::cerr << "The texture failed to load!! ERROR: " << SDL_GetError() << std::endl;
    }

    // Return the texture.
    return texture;
}

// Destroys the window. Used when closing the window.
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

// Gets the position of the window. 
// TODO: This line Does nothing since it's "void" (aka doesn't return anything). Make it return something! 
void RenderWindow::getWinPos(int *WinPosX, int *WinPosY)
{
    SDL_GetWindowPosition(window, WinPosX, WinPosY);
}

// Clears the rendered image.
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

// Render the rectangle, Looks for the entity class.
// Takes the Entity value and the scale factor.
void RenderWindow::render(Entity& p_entity, int Pos_h)
{
    // Render a rectangle from source. Takes the x, y , w(idth) and h(eight) of the rectangle.
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x; 
    src.y = p_entity.getCurrentFrame().y; 
    src.w = p_entity.getCurrentFrame().w; 
    src.h = p_entity.getCurrentFrame().h; 

    // Render a rectangle to the destination. Takes the x, y , w(idth) and h(eight) of the rectangle.
    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getCurrentFrame().w * Pos_h;
    dst.h = p_entity.getCurrentFrame().h * Pos_h;
    
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

// Displays the rendered image.
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
