#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"

/**
 * \brief This class represents the RenderWindow in the game.
 * The RenderWindow is the window in which the game is rendered.
 * It is used to store information about the window, such as its
 * width, height, and title. It is also used to render the game
 * to the screen. - Copilot
 */
class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  SDL_Texture *loadTexture(const char *p_filePath);
  void GLInit();
  void cleanUp();
  int getWinPos(int *WinPosX, int *WinPosY);
  void getWindowSize(int *w, int *h);
  void clear();
  void resetSize();
  void setWindowSize(int w, int h);
  void setFullscreen(bool fullscreen);
  void render(Entity &p_entity, int Pos_w, int Pos_h);
  void display();
  void swap();
  void ImGuiInit();
  void ImGuiRenderStart();
  void ImGuiRenderFinish();
  void ImGuiShutdown();

private:
  /**
   * \brief Create a window with the title, position of the window (x,y) are
   * undefined, the (w,h) and show the window. \param p_title Title of the
   * window \param p_w Width of the window \param p_h Height of the window.
   */
  SDL_Window *window;
  // Create the render space for the window.
  // See SDL_CreateRenderer documentation.
  SDL_Renderer *renderer;
  SDL_GLContext *context;
};
