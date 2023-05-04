/**
 * @file main.cpp
 * @author Midou (midou@midou.dev)
 * @version 0.1
 * @date 2023-04-17
 * 
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "renderwindow.hpp"
#include "entity.hpp"
#include "math.hpp"
#include "mplayer.hpp"

// Screen resolution.
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  720
#define FPS            60

// Setup the delta time.
Uint32 lastTicks = SDL_GetTicks64();


// Smooth move.
float move(int p_x, int p_y) {
    int x = p_x;
    int y = p_y;
    if (p_x > x && p_y > y) {
        int i;
        for (i; i < p_x; i++) {
            x = exp(x);
        }
        return x, y;
    }
    else {
        return sqrt((p_x * p_x) + (p_y * p_y));
    }

    return 0;
}



int main(int argc, char* args[]) {
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

        
        MusicPlayer music; 

        music.initMusic();
        music.openAudio();
        //Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS );
        //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
            std::cerr << "Failed to open audio! ERROR: " << Mix_GetError() << std::endl;
        }
        // TODO: Make this thing usable.
        //Mix_Music* musicPlayer = music.loadMusic("src/res/bgm/bg.ogg");
        
        Mix_Music* musicPlayer = Mix_LoadMUS("src/res/bgm/bgm.ogg");
        Mix_PlayMusic(musicPlayer, -1);

        if (musicPlayer == NULL) {
            std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
        }
        
        //music.openAudio();
        //music.playMusic();
        
        RenderWindow window("DEMO ENGINE v0.0.1", SCREEN_WIDTH, SCREEN_HEIGHT);
                

        // Load the texture.
        // \param p_filePath Path to load the texture to faceSprite.
        SDL_Texture* faceSprite = window.loadTexture("src/res/img/pop.png");

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

        int XPos_mo_sta = 1; 
        int YPos_mo_sta = 1;

        int Mus = 0;
        
        bool fs; 

        // Scale of the entity. Y axis. 
        int YPos_wh = 1;

        while (gameRunning){
            Uint32 nowTicks = SDL_GetTicks64();

            // Dt in seconds
            float deltaTime = (nowTicks - lastTicks) * 0.001f;

            lastTicks = nowTicks;



            while (SDL_PollEvent(&event)){
                std::vector<Entity> entities = {
                               Entity(Vector2f(XPos1,YPos1), faceSprite),
                               Entity(Vector2f(XPos_mo_sta,YPos_mo_sta), faceSprite),
                               Entity(Vector2f(XPos2,YPos2), faceSprite)
                };
                
                // Poll the close event  
                if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_a ) {
                    gameRunning = false;
                }
                //User presses a key
                else if( event.type == SDL_KEYDOWN ) {
                   switch (event.key.keysym.sym) {
                        case SDLK_z:
                        for (int i=0; i < 50; i++) {
                        std::cout << "UP!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        YPos2 = (YPos2 - 0.01) * YPos_wh  * 0.5;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        }
                        break;
                        
                        case SDLK_s:
                        std::cout << "DOWN!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        YPos2 = YPos2 +10 * YPos_wh ;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_q:
                        std::cout << "LEFT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos2 = XPos2 -10 * YPos_wh ;
                        std::cout << YPos2 << " <-- YPos After" << std::endl;
                        break;
                                                                               
                        case SDLK_d:
                        std::cout << "RIGHT!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        XPos2 = XPos2 +10 * YPos_wh ;
                        std::cout << YPos2 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_UP:
                        std::cout << "UP!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        YPos1 = YPos1 -10 * YPos_wh ;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_DOWN:
                        std::cout << "DOWN!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        YPos1 = YPos1 +10 * YPos_wh ;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_LEFT:
                        std::cout << "LEFT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos1 = XPos1 -10 * YPos_wh ;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;
                                                                               
                        case SDLK_RIGHT:
                        std::cout << "RIGHT!" << std::endl;
                        std::cout << YPos1 << " <-- YPos Before" << std::endl;
                        XPos1 = XPos1 +10 * YPos_wh ;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
                        break;

                        case SDLK_r:
                        std::cout << "RESET!" << std::endl;
                        
                            XPos1 = 0;
                            YPos1 = 0;
                            XPos2 = 240;
                            YPos2 = 240;
                            XPos_mo_sta = 1;
                            YPos_mo_sta = 1;
                            YPos_wh = 1;
                            window.resetSize();
                            window.setFullscreen(false);
                        break;

                        case SDLK_k:
                        std::cout << "Set the window size to 1080p" << std::endl;
                        window.setWindowSize(1920, 1080);
                        break; 

                        case SDLK_f:
                        std::cout << "Fullscreen" << std::endl;
                        fs = false;
                        if (fs == true) {
                            window.setFullscreen(false);
                            fs = false;
                        }
                        else {
                        window.setFullscreen(true);
                        fs = true;
                        }
                        break;

                        case SDLK_SPACE:
                            if ( Mus == 1 ) {
                                Mix_ResumeMusic();
                                Mus = 0;
                            }
                            else {Mix_PauseMusic(); Mus = 1;};
                        break;
                   } 
                
                }

                else if (event.type == SDL_KEYUP ){
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                        for (int i=0; i < 50; i++) {
                        SDL_Delay(10);
                        YPos2 = (YPos2 - 0.5) * YPos_wh * deltaTime / 2;
                        
                    }
                        break;
                    
                    }
                }
                else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                            XPos_mo = { event.motion.x };
                            YPos_mo = { event.motion.y };
                            std::cout << "CLICK LEFT!" << std::endl;
                            XPos_mo_sta = XPos_mo;
                            std::cout << "XPos_mo_sta is " << XPos_mo_sta << "." << std::endl;
                            YPos_mo_sta = YPos_mo;
                            std::cout << "YPos_mo_sta is " << YPos_mo_sta << "." << std::endl;
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

                if ((nowTicks - lastTicks) > 1000) {
                    lastTicks = 0;
                }

                // Reminder: Condition ? value if true : value if false
                float fps = (deltaTime > 0) ? 1000.0f / deltaTime : 0.0f;

                if (deltaTime != 0) {
                std::cout << "FPS: " << fps << "." << std::endl;
                std::cout << "TimeStart : " << nowTicks << "." << std::endl;
                std::cout << "TimeEnd : " << lastTicks << "." << std::endl;
                }       



                window.getWinPos(WPosX, WPosY);
                std::cout << "Position of window is " << WPosX << "," << WPosY << "." << std::endl;
//                std::vector<Entity> entities = {
//                               Entity(Vector2f(XPos1,YPos1), faceSprite),
//                               Entity(Vector2f(XPos_mo-120,YPos_mo-120), faceSprite),
//                               Entity(Vector2f(XPos2,YPos2), faceSprite)
//                };

                // Clear the render
                window.clear();
                // Render the faces (3)
                     for (Entity& face : entities){                
                        window.render(face, XPos_mo_sta, YPos_mo_sta); 
                    };
                // Update the render with a new frame.
                window.display();

                // Reduce the CPU usage.                                              
                SDL_Delay(1);



            }
           
            
        }
        // Close the audio.
        music.closeAudio();
        // Free the chunk.
        music.freeMusic();
        // Destroy the window.
        window.cleanUp();
        std::cout << "-----------------------[ SDL EXITING ! ]-----------------------"  << std::endl;
        // Quit SDL
        SDL_Quit();
        // Return a successful exit code.
        return 0;
}



