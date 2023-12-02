#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <iostream>
//#include <tuple>
#include "entity.hpp"
#include "renderwindow.hpp"

// Creates a new window to render content in it.
// Takes the Title name, w(idth) and h(eight) of the window.
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
//
        
//
        // Create a pointer for window and render and point them to NULL.
        :window(NULL), renderer(NULL)
        {
            window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
            // Fail if the window did not init.
            if (window == NULL) {
            std::cerr << "Window failed to init, ERROR: " << SDL_GetError() << std::endl;
            }

            SDL_GLContext context;
            context = SDL_GL_CreateContext(window); 
            gladLoadGLLoader(SDL_GL_GetProcAddress);
            SDL_GL_MakeCurrent(window, context);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
 
 
 
 
 
 
 
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

void RenderWindow::GLInit() {

// Stub.

}


// Destroys the window. Used when closing the window.
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

// Gets the position of the window. 
// Takes the x and y position of the window.
// Returns the position of the window.

// usage of auto before declaring the function.
// auto is used to automatically deduce the type of the variable that is being declared.
// In this case, the type of the variable is std::tuple<int, int>.
// std::tuple is a class that is used to return multiple values from a function.
// In this case, the function returns the x and y position of the window.
// The function returns a tuple of two integers.
// The first integer is the x position of the window.
// The second integer is the y position of the window.
// The function takes two pointers to integers as parameters.
//
int RenderWindow::getWinPos(int *WinPosX, int *WinPosY)
{
    SDL_GetWindowPosition(window, WinPosX, WinPosY);
    //return std::make_tuple(*WinPosX, *WinPosY);
    return 0;
   }
// Clears the rendered image.
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::resetSize()
{
    SDL_SetWindowSize(window, 1280, 720);
}

void RenderWindow::setWindowSize(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}

void RenderWindow::setFullscreen(bool fullscreen)
{
    if (fullscreen == false)
        SDL_SetWindowFullscreen(window, 0);
    else { 
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
}

/** Render the rectangle, Looks for the entity class.
/  Takes the Entity value and the scale factor.
/  @param Entity The entity to render.
/  @param Pos_w The scale factor for the width.  
/  @param Pos_h The scale factor for the height.
*/
void RenderWindow::render(Entity& p_entity, int Pos_w, int Pos_h)
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
    dst.w = p_entity.getCurrentFrame().w * Pos_w;
    dst.h = p_entity.getCurrentFrame().h * Pos_h;
    
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

// Displays the rendered image.
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

// Swap the buffers.
void RenderWindow::swap()
{
    SDL_GL_SwapWindow(window);
}


