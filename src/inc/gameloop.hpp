#pragma once

#include "mplayer.hpp"
#include "renderwindow.hpp"
#include "shader.hpp"
#include <SDL2/SDL.h>
#include <string>

struct GameLoop {

  float getframes(Uint32 start);
  std::string logs();
  void init();  // Initialisation of critcal game components.
  void loop();  // The main game loop.
  void close(); // Close the game loop.

private:
  // This going to be comically awful. I doubt it's what I'm supposed to do,
  // right?
  bool gameRunning;
  SDL_Event event;
  RenderWindow window;
  bool fs, wireframe;
  struct gl_color {
    float r, g, b;
  };
  gl_color gl_color;
  bool Mus;
  int YPos_wh;
  MusicPlayer music;
  unsigned int VBO, VAO;
  unsigned int texture1, texture2;
  Shader shader;
};

// What the fuck am I also supposed to do here..don't include this file yet!
