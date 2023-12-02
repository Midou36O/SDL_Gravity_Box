/**
 * @file main.cpp
 * @author Midou (midou@midou.dev)
 * @version 0.1
 * @date 2023-04-17
 * 
 */

#include "glad/glad.h"  
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
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
// Allow the keystate to be saved.
const Uint8* keystate = SDL_GetKeyboardState(NULL); 

// Vert and Frag Sources.
const char *vrtxShdrSrc =   "#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                            "}\0";
const char *frgmntShdrSrc = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "uniform vec4 ourColor;\n" // ourColor essentially comes from fragment shader, we'll declare it.
                            "void main()\n"
                            "{\n"
                            "   FragColor = ourColor;\n" 
//                          "   FragColor = vec4(.5f, 0.0f, 0.0f, 1.0f);\n"
                            "}\n\0";


float vertices[] = {
  -0.5f, -0.5f, 0.0f, // left  
   0.5f, -0.5f, 0.0f, // right 
   0.0f,  0.5f, 0.0f  // top
};


int main(int argc, char* args[]) {
 
        // Clear the files before starting the game.
        std::ofstream ofs;
        ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);  
        ofs.close();
        ofs.open("error.txt", std::ofstream::out | std::ofstream::trunc);   
        ofs.close(); 

        // Add some files to this code.
        freopen( "output.txt", "w", stdout);
        freopen( "error.txt", "w", stderr );

        std::cout << "-----------------------[ SDL START ! ]-----------------------"  << std::endl;
        // Add OpenGL Contexts.
        // TODO: This should be out of this file. Currently i have to declare this before SDL even inits the window and the context for some reason.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);                          
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);                          
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);                                   
        
        
        
        // Init the SDL video.
        if (SDL_Init(SDL_INIT_VIDEO) > 0 ) {
        std::cerr << "SDL_Init defenitely failed here... ERROR: " << SDL_GetError() << std::endl;
        return 1;
        }
        // Init the image.
        if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "IMG_Init failed, but this is still a good progress! ERROR: " << SDL_GetError() << std::endl;
        return 1;
        }
          // For some reason this breaks the code, investigate please.
        // Init GLAD.
        //if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        //std::cerr << "Failed to initialize GLAD. ERROR: " << SDL_GetError() << std::endl;
        //return 1;
        //}

      RenderWindow window("DEMO ENGINE v0.0.1", SCREEN_WIDTH, SCREEN_HEIGHT); 

      // OpenGL Code, to be moved properly later.
      
      window.GLInit();

      unsigned int VBO, VAO;
      // Generate the buffer. Takes the number of buffers and the buffer.
      glGenBuffers(1, &VBO);
      // Bind the buffer. Takes the type of the buffer and the buffer.
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      // Buffer the data. Takes the type of the buffer, the size of the data, the data, and the usage of the buffer.
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


      unsigned int vrtxShdr, frgmntShdr;
      vrtxShdr = glCreateShader(GL_VERTEX_SHADER);
      frgmntShdr = glCreateShader(GL_FRAGMENT_SHADER);
      // Takes the shader, the number of strings, the string, and the length of the string.
      glShaderSource(vrtxShdr, 1, &vrtxShdrSrc, NULL); 
      glShaderSource(frgmntShdr, 1, &frgmntShdrSrc, NULL);
      glCompileShader(vrtxShdr);
      glCompileShader(frgmntShdr);
  

      unsigned int shdrPrg;
      shdrPrg = glCreateProgram();
      // You're in page 33 of the book. Chapter 5.5 Linking Vertex Attributes. The top.
      glAttachShader(shdrPrg,vrtxShdr);
      glAttachShader(shdrPrg,frgmntShdr);
      glLinkProgram(shdrPrg);
      glUseProgram(shdrPrg);
      glDeleteShader(vrtxShdr);
      glDeleteShader(frgmntShdr);

      /*
      * The vertex attribute interprets the vertex data (per vertex attribute.) It takes the following options. 
      *
      * \param 0 Location of the vertex
      * \param 3 The length of the vertex
      * \param GL_FLOAT The type of the data
      * \param GL_FALSE Normalize the data? As in. If it's float, it goes float, if it's signed, it does signed, if it's integer, it goes integer.
      * \param 3 * sizeof(float) The stride of the data. 
      * \param (void*)0 The offset of the data.
      */
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      

  // End OpenGL Code.
        MusicPlayer music; 

        music.initMusic();
        music.openAudio();
        int audiostat = music.openAudio();
        if (audiostat == -1) {
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

        float g = 0.0f;
        
        bool fs; 

        // Scale of the entity. Y axis. 
        int YPos_wh = 1;

        while (gameRunning){
            // Clear the render
            window.clear();

            Uint32 nowTicks = SDL_GetTicks64();

            // Dt in seconds
            float deltaTime = (nowTicks - lastTicks) * 0.001f;

            lastTicks = nowTicks;
            float fps = 1.0f / deltaTime;

            float timeValue = (float)SDL_GetTicks64()/100; // No idea if that will work, but we're supposed to get the time in milliseconds to seconds.                                                                                                                 
            float greenValue = (sin(timeValue)/ 2.0f) + 0.5f; // sinus function is there since we're using cmath don't worry. Get the time value in seconds, divide it by 2, and add, 0.5f. The sinus function we made essentially avoids going to negative values. 

            int count = 0;
            if (count == 1000) {
            std::cout << "[SEC]: "<< timeValue << " seconds elapsed." << std::endl;
            std::cout << "[SIN]: the sine is " << greenValue << std::endl;
            count = 0;
            }
            count++;
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
                        std::cout << "UP!" << std::endl;
                        std::cout << YPos2 << " <-- YPos Before" << std::endl;
                        YPos2 = (YPos2 - 0.01) * YPos_wh  * 0.5;
                        std::cout << YPos1 << " <-- YPos After" << std::endl;
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

                        default:
                        break;
                   } 
                
                }
                
                
                
                    //continuous-response keys
                    if(keystate[SDL_SCANCODE_LEFT])
                    {
                     XPos1 = XPos1 - 10 * YPos_wh;
                    }
                    if(keystate[SDL_SCANCODE_RIGHT])
                    {
                      XPos1 = XPos1 + 10 * YPos_wh;
                    }
                    if(keystate[SDL_SCANCODE_UP])
                    {
                      YPos1 = YPos1 - 10 * YPos_wh;
                    }
                    if(keystate[SDL_SCANCODE_DOWN])
                    {
                      YPos1 = YPos1 + 10 * YPos_wh;
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
                    g=g+0.2f;
                    YPos_wh++;
                 } else if (event.wheel.y < 0 ) {
                    if (YPos_wh <= 1) {
                        YPos_wh = 1;
                    } else {
                    g=g-0.2f; 
                    YPos_wh--;
                    }
                 }
                
                 std::cout << "Scrolling is at" << YPos_wh << "." << std::endl;
                }  
            
                
                
                // Reminder: Condition ? value if true : value if false
                float fps = (deltaTime > 0) ? 1000.0f / deltaTime : 0.0f;

                if (deltaTime != 0) {
                std::cout << "FPS: " << fps << "." << std::endl;
                std::cout << "TimeStart : " << nowTicks << "." << std::endl;
                std::cout << "TimeEnd : " << lastTicks << "." << std::endl;
                }       


                // Get window position.
                window.getWinPos(WPosX, WPosY);
                //std::cout << "Window position is " << SDL_GetWindowPosition(window.window, WPosX, WPosY) << "." << std::endl;
                std::cout << "Window position is " << 0 << "," << 0 << "." << std::endl;

//                std::vector<Entity> entities = {
//                               Entity(Vector2f(XPos1,YPos1), faceSprite),
//                               Entity(Vector2f(XPos_mo-120,YPos_mo-120), faceSprite),
//                               Entity(Vector2f(XPos2,YPos2), faceSprite)
//                };
            // Yeah yeah i know this is OpenGL again but deal with it B) 

            glViewport(0+SCREEN_WIDTH/4, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
            glUseProgram(shdrPrg);
            int vertexColorLoc = glGetUniformLocation(shdrPrg, "ourColor"); 
            glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glClearColor(0.0f, g, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
       
            // End OpenGL Code.
                // Render the faces (3)
                // NOTE: Interesting, quitting the engine crashes the game when this is here.
                // NOTE: Removing this piece of code stops the frame updates. Investigate.
                // NOTE: Check the SDL Polling event. It Delays after excessive usage of mouse movement and slows the rendering.
                     for (Entity& face : entities){                
                        window.render(face, XPos_mo_sta, YPos_mo_sta); 
                    };
                // Update the render with a new frame.
                window.display();
                window.swap(); 

                // Reduce the CPU usage.                                              
                SDL_Delay(1);


            }
           
            
        }
        // Make sure things close properly.
        SDL_Delay(3);
        // Close the audio.
        music.closeAudio();
        // Free the chunk.
        music.freeMusic();
        // Allow the music player to close properly too.
        SDL_Delay(3);
        // Destroy the window.
        window.cleanUp();
        std::cout << "-----------------------[ SDL EXITING ! ]-----------------------"  << std::endl;
        // Quit SDL
        SDL_Quit();
        // Return a successful exit code.
        return 0;
}



