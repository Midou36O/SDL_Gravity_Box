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
// #include <SDL2/SDL_opengl.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
// #include <string>

#include "mplayer.hpp"
#include "renderwindow.hpp"
#include "shader.hpp"

// Import dearimgui
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

// Screen resolution.
#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720
#define TARGET_FPS 60

int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;

// Setup the delta time.
Uint32 lastTicks = SDL_GetTicks64();
// Allow the keystate to be saved.
const Uint8 *keystate = SDL_GetKeyboardState(NULL);

float vertices[] = {
    // Since we're going to implement multiple colors now, we're going to have
    // to separate the vertices:
    //             VERTEX     COLOR
    // STRUCTURE: [X][Y][Z][R][G][B]...
    // Vertices             Colors
    // 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left, RED
    //-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right, GREEN
    // 0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top, BLUE

    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left, RED
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right, GREEN
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top, BLUE
};

std::string printVertices() {
  std::string verticesString = "";
  for (int i = 0; i < 18; i++) {
    verticesString += std::to_string(vertices[i]) + " ";
  }
  return verticesString;
}

int main(int argc, char *args[]) {

  // Clear the files before starting the game.
  std::ofstream ofs;
  ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  ofs.open("error.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();

  // Add some files to this code.
  freopen("output.txt", "w", stdout);
  freopen("error.txt", "w", stderr);

  std::cout << "-----------------------[ SDL START ! ]-----------------------"
            << std::endl;

  // Init the image.
  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cerr << "IMG_Init failed, but this is still a good progress! ERROR: "
              << SDL_GetError() << std::endl;
    return 1;
  }
  // For some reason this breaks the code, investigate please.

  RenderWindow window("DEMO ENGINE v0.0.1", DEFAULT_SCREEN_WIDTH,
                      SCREEN_HEIGHT);

  // OpenGL Code, to be moved properly later.

  window.GLInit();
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Imgui init
  window.ImGuiInit();

  Shader shader("src/res/shaders/vertx_shader.vs",
                "src/res/shaders/frag_shader.fs");

  unsigned int VBO, VAO;
  // Generate the buffer. Takes the number of buffers and the buffer.
  // Vertex
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  if (glGetError() > 0) {
    std::cerr << "Error!: " << glGetError() << std::endl;
  }

  /*
   * The vertex attribute interprets the vertex data (per vertex attribute.)
   * It takes the following options.
   *
   * \param 0 Location of the vertex
   * \param 3 The length of the vertex
   * \param GL_FLOAT The type of the data
   * \param GL_FALSE Normalize the data? As in. If it's float, it goes float,
   * if it's signed, it does signed, if it's integer, it goes integer. \param
   * 3 * sizeof(float) The stride of the data. \param (void*)0 The offset of
   * the data.
   */
  // 3 to 6 since we're now using 3 colors and vertexes.

  MusicPlayer music;

  music.initMusic();
  music.openAudio();
  int audiostat = music.openAudio();
  if (audiostat == -1) {
    std::cerr << "Failed to open audio! ERROR: " << Mix_GetError() << std::endl;
  }
  //  TODO: Make this thing usable.
  // Mix_Music* musicPlayer = music.loadMusic("src/res/bgm/bg.ogg");

  Mix_Music *musicPlayer = Mix_LoadMUS("src/res/bgm/bgm.ogg");
  Mix_PlayMusic(musicPlayer, -1);

  if (musicPlayer == NULL) {
    std::cerr << "Failed to load music! ERROR: " << Mix_GetError() << std::endl;
  }

  // music.openAudio();
  // music.playMusic();

  // Load the texture.
  // \param p_filePath Path to load the texture to faceSprite.
  // SDL_Texture *faceSprite = window.loadTexture("src/res/img/pop.png");

  // Entity entities[3] = { Entity(0,0, faceSprite),
  //                      Entity(120,120, faceSprite),
  //                      Entity(240,240, faceSprite)
  //};

  // Game is running (true) by default.
  // This is currently used to keep the game up after rendering the frame.
  bool gameRunning = true;

  // Create a dummy SDL_Event to poll the events.
  SDL_Event event;

  int Mus = 0;

  // OpenGL background color.
  struct gl_color {
    float r;
    float g;
    float b;
  };
  gl_color gl_color = {0.0f, 0.0f, 0.0f};
  // What a mess.

  bool fs;
  bool wireframe = false;

  // Scale of the entity. Y axis.
  int YPos_wh = 1;

  while (gameRunning) {
    // The loop goes as following:
    // 6. Clear and swap the buffer.
    // 2. Clear the render.
    // 3. Get the delta time.
    // 4. Render
    // 5. Update the render with a new frame.
    // 1. Poll the events.
    // repeat.

    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      // Poll the close event
      if (event.type == SDL_QUIT) { // How the FUCK is event.key.keysym.sym
                                    // SDLK_a causing the engine to close when
                                    // using dearImGui??
        gameRunning = false;
      }
      // User presses a key
      else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_z:
          break;

        case SDLK_s:
          break;

        case SDLK_q:
          break;

        case SDLK_d:
          break;

        case SDLK_r:
          std::cout << "RESET!" << std::endl;
          window.resetSize();
          window.setFullscreen(false);
          window.clear();
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
          } else {
            window.setFullscreen(true);
            fs = true;
          }
          break;

        case SDLK_SPACE:
          if (Mus == 1) {
            Mix_ResumeMusic();
            Mus = 0;
          } else {
            Mix_PauseMusic();
            Mus = 1;
          };
          break;

        default:
          break;
        }
      }

      // Get the mouse position on the window.
      else if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) {
          YPos_wh++;
        } else if (event.wheel.y < 0) {
          if (YPos_wh <= 1) {
            YPos_wh = 1;
          } else {
            YPos_wh--;
          }
        }
      }

      // if (20 > (SDL_GetTicks() - lastTicks)) {
      //   SDL_Delay(20 - (SDL_GetTicks() -
      //                   lastTicks)); // SDL_Delay pauses the execution.
      // }
    }
    // Swap the buffer
    // FIXME: It's flickering!
    // window.swap();

    // Get the delta time.
    Uint32 nowTicks = SDL_GetTicks64();

    // Dt in seconds
    float deltaTime = (nowTicks - lastTicks) * 0.001f;

    lastTicks = nowTicks;
    // FPS to be displayed.
    float fps = 1.0f / deltaTime;

    float timeValue = (float)SDL_GetTicks64() / 100;
    // No idea if that will work, but we're supposed to
    // get the time in milliseconds to seconds.
    double greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    // sinus function is there since we're using cmath don't worry.
    // Get the time value in seconds, divide it by 2, and add, 0.5f.
    // The sinus function we made essentially avoids going to negative
    // values.

    // Update window width and height.
    window.getWindowSize(&SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Limit the FPS to FPS_target.
    // if (deltaTime < 1.0f / TARGET_FPS) {
    //   int delayTime = (int)((1.0f / TARGET_FPS - deltaTime) * 1000.0f);
    //   SDL_Delay(delayTime);
    // }
    // std::vector<Entity> entities = {
    //     Entity(Vector2f(XPos1, YPos1), faceSprite),
    //     Entity(Vector2f(XPos_mo_sta, YPos_mo_sta), faceSprite),
    //     Entity(Vector2f(XPos2, YPos2), faceSprite)};

    //// Get window position.
    // window.getWinPos(WPosX, WPosY);
    //// std::cout << "Window position is " <<
    //// SDL_GetWindowPosition(window.window, WPosX, WPosY) << "." <<
    /// std::endl;
    // std::cout << "Window position is " << 0 << "," << 0 << "." <<
    // std::endl;

    //                std::vector<Entity> entities = {
    //                               Entity(Vector2f(XPos1,YPos1),
    //                               faceSprite),
    //                               Entity(Vector2f(XPos_mo-120,YPos_mo-120),
    //                               faceSprite),
    //                               Entity(Vector2f(XPos2,YPos2), faceSprite)
    //                };
    //
    // Dear ImGui stuff.
    window.ImGuiRenderStart();
    // FPS window
    ImGui::Begin("FPS");
    ImGui::Text("FPS: %f", fps);
    ImGui::Text("Delta time: %f", deltaTime);
    ImGui::Text("Time running: %d seconds.", SDL_GetTicks() / 1000);
    ImGui::End();
    // Window resolution window
    ImGui::Begin("Window resolution");
    ImGui::Text("Window resolution is %d, %d", SCREEN_WIDTH, SCREEN_HEIGHT);
    ImGui::End();
    // Triangle pos window
    ImGui::Begin("Triangle position And Color");
    // Color edit
    ImGui::ColorEdit3("Triangle color1", &vertices[3]);
    ImGui::ColorEdit3("Triangle color2", &vertices[9]);
    ImGui::ColorEdit3("Triangle color3", &vertices[15]);
    ImGui::SliderFloat3("Position1", &vertices[0], -1.0f, 1.0f);
    ImGui::SliderFloat3("Position2", &vertices[6 + 0], -1.0f, 1.0f);
    ImGui::SliderFloat3("Position3", &vertices[12 + 0], -1.0f, 1.0f);
    // Wireframe mode
    ImGui::Checkbox("Wireframe mode", &wireframe);
    ImGui::End();
    // OpenGL background color window
    ImGui::Begin("OpenGL background color");
    ImGui::ColorEdit3("Background color", &gl_color.r);
    ImGui::End();
    // Print the sine wave window
    ImGui::Begin("Sine wave");
    ImGui::Text("Sine wave: %f", greenValue);
    ImGui::End();
    // Overlay of opengl debug
    ImGui::Begin("OpenGL debug");
    ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
    ImGui::Text("OpenGL Vendor: %s", glGetString(GL_VENDOR));
    ImGui::Text("OpenGL Renderer: %s", glGetString(GL_RENDERER));
    ImGui::Text("OpenGL Shading Language Version: %s",
                glGetString(GL_SHADING_LANGUAGE_VERSION));
    ImGui::End();
    ImGui::Render();

    // window.ImGuiRenderFinish();

    // Yeah yeah i know this is OpenGL again but deal with it B)
    // Run wireframe mode if checked.
    if (wireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    // Since we're now having 2 vertexes we need to delay the offset location.
    // TODO: Explain this better!
    // Color
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glViewport(0 + DEFAULT_SCREEN_WIDTH / 4, 0, SCREEN_WIDTH / 2,
    // SCREEN_HEIGHT); glViewport(0, 0, DEFAULT_SCREEN_WIDTH * 2, SCREEN_HEIGHT
    // * 2);
    // glViewport(0, 0, DEFAULT_SCREEN_WIDTH, SCREEN_HEIGHT);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    shader.use();
    if (glGetError() > 0) {
      std::cerr << glGetError() << std::endl;
    }
    // int vertexColorLoc = glGetUniformLocation(shdrPrg, "ourColor");
    // glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);

    glClearColor(gl_color.r, gl_color.g, gl_color.b, 1.0f);
    if (glGetError() > 0) {
      std::cerr << glGetError() << std::endl;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    if (glGetError() > 0) {
      std::cerr << glGetError() << std::endl;
    }
    glBindVertexArray(VAO);
    if (glGetError() > 0) {
      std::cerr << glGetError() << std::endl;
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
    if (glGetError() > 0) {
      std::cerr << glGetError() << std::endl;
    }

    // End OpenGL Code.
    // Render the faces (3)
    // for (Entity &face : entities) {
    //  window.render(face, XPos_mo_sta, YPos_mo_sta);
    //};
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Update the render with a new frame.
    // window.display();
    // Swap the buffer
    window.swap();
    // Clear the render
    window.clear();
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
  // Destroy imgui.
  window.ImGuiShutdown();
  std::cout << "-----------------------[ SDL EXITING ! ]-----------------------"
            << std::endl;
  // Quit SDL
  SDL_Quit();
  // Return a successful exit code.
  return 0;
}
