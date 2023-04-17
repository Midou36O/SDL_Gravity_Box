/**
 * @file main.cpp
 * @author Midou (midou@midou.dev)
 * @version 0.1
 * @date 2023-04-17
 * 
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "renderwindow.hpp"
#include "entity.hpp"
#include "math.hpp"

// Screen resolution.
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Setup the delta time.
double CurrentTime = SDL_GetTicks64();


int main(int argc, char* args[]){
        // Add some files to this code.
        freopen( "output.txt", "w", stdout);
        freopen( "error.txt", "w", stderr );

        std::cout << "-----------------------[ SDL START ! ]-----------------------"  << std::endl;

        // Init the SDL video.
        if (SDL_Init(SDL_INIT_VIDEO) > 0 ) {
        std::cerr << "SDL_Init defenitely failed here... ERROR: " << SDL_GetError() << std::endl;
        return 2;
    }
        // Init the image.
        if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "IMG_Init failed, but this is still a good progress! ERROR: " << SDL_GetError() << std::endl;
        return 3;
        }

        RenderWindow window("GAME v1.0", SCREEN_WIDTH, SCREEN_HEIGHT);
                

        // Load the texture.
        // \param p_filePath Path to load the texture to faceSprite.
        SDL_Texture* faceSprite = window.loadTexture("res/img/pop.png");

        // Entity entities[3] = { Entity(0,0, faceSprite),
        //                      Entity(120,120, faceSprite),
        //                      Entity(240,240, faceSprite)
        //};


       
       
        
        // Game is running (true) by default.
        // This is currently used to keep the game up after rendering the frame.        
        bool gameRunning = true;
        // Create a dummy SDL_Event to poll the events.
        SDL_Event event;


        // Position of the first entity. X axis.
        int XPos1 = 0;
        // Position of the first entity. Y axis.
        int YPos1 = 0;

        // Position of the second entity. X axis.
        int XPos2 = 240;
        // Position of the second entity. Y axis.
        int YPos2 = 240;

        // Window position. X axis.
        int *WPosX = 0;
        // Window position. Y axis.
        int *WPosY = 0;

        // Position of the mouse. X axis.
        int XPos_mo = 0;
        // Position of the mouse. Y axis.
        int YPos_mo = 0;

        // Scale of the entity. Y axis. 
        int YPos_wh = 1;

        while (gameRunning){
            while (SDL_PollEvent(&event)){
                // Poll the close event  
                if (event.type == SDL_QUIT) {
                    gameRunning = false;
                }
                //User presses a key
                else if( event.type == SDL_KEYDOWN ) {
                   switch (event.key.keysym.sym) {
                        case SDLK_z:
                        std::cout << "UP!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        YPos2 = YPos2 -10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_s:
                        std::cout << "DOWN!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        YPos2 = YPos2 +10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_q:
                        std::cout << "LEFT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos2 = XPos2 -10 * YPos_wh;
                        std::cout << YPos2 << " <-- YPos After" << std::endl;
                        break;
                                                                               
                        case SDLK_d:
                        std::cout << "RIGHT!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        XPos2 = XPos2 +10 * YPos_wh;
                        std::cout << YPos2 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_UP:
                        std::cout << "UP!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        YPos1 = YPos1 -10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_DOWN:
                        std::cout << "DOWN!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        YPos1 = YPos1 +10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_LEFT:
                        std::cout << "LEFT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos1 = XPos1 -10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;
                                                                               
                        case SDLK_RIGHT:
                        std::cout << "RIGHT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos1 = XPos1 +10 * YPos_wh;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;
                   } 
                }

                // Get the mouse position on the window.
                else if (event.type == SDL_MOUSEMOTION) {   
                 XPos_mo = { event.motion.x };
                 YPos_mo = { event.motion.y };
                 std::cout << "Position of mouse is " << XPos_mo << "," << YPos_mo << "." << std::endl;
                }  
                else if (event.type == SDL_MOUSEWHEEL) {   
                 if (event.wheel.y > 0 ){
                    YPos_wh++;
                 } else if (event.wheel.y < 0 ) {
                    if (YPos_wh <= 1) {
                        YPos_wh = 1;
                    } else {
                    YPos_wh--;
                    }
                 }
                 
                 std::cout << "Scrolling is at" << YPos_wh << "." << std::endl;
                }  
                double LastTime = SDL_GetTicks64();
                double DeltaTime = ( LastTime - CurrentTime ) / 1000.0f;

                if (DeltaTime != 0) {
                std::cout << "FPS: " << DeltaTime << "." << std::endl;
                std::cout << "TimeStart : " << CurrentTime << "." << std::endl;
                std::cout << "TimeEnd : " << LastTime << "." << std::endl;
                }       

                window.GetWinPos(WPosX, WPosY);
                std::cout << "Position of window is " << WPosX << "," << WPosY << "." << std::endl;
                std::vector<Entity> entities = {
                               Entity(Vector2f(XPos1,YPos1), faceSprite),
                               Entity(Vector2f(XPos_mo-120,YPos_mo-120), faceSprite),
                               Entity(Vector2f(XPos2,YPos2), faceSprite)
                };

                // Clear the render
                window.clear();
                // Render the faces (3)
                     for (Entity& face : entities){                
                        window.render(face, YPos_wh); 
                    };
                // Update the render with a new frame.
                window.display();                                              




            }
           
            
        }
        // Destroy the window.
        window.cleanUp();
        std::cout << "-----------------------[ SDL EXITING ! ]-----------------------"  << std::endl;
        // Quit SDL
        SDL_Quit();
        // Return a successful exit code.
        return 0;
}



