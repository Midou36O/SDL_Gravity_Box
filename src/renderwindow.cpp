#include "SDL_video.h"
#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_opengl.h>
#include <iostream>
#include <stdio.h>
// #include <tuple>
#include "entity.hpp"
#include "renderwindow.hpp"

// Imgui
#include "submodules/imgui/backends/imgui_impl_opengl3.h"
#include "submodules/imgui/backends/imgui_impl_sdl2.h"
#include "submodules/imgui/imgui.h"

#define GL3_PROTOTYPES 1

// Creates a new window to render content in it.
// Takes the Title name, w(idth) and h(eight) of the window.
RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)

    // Create a pointer for window and render and point them to NULL.
    : window(NULL), renderer(NULL) {

  // Fail if SDL_Init did not init.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL failed to init, ERROR: " << SDL_GetError() << std::endl;
  }

  int check = true;
  // Don't mind the dogshit code below, it's just a bunch of checks to make
  // sure that the OpenGL context is created properly.
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
  // if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG) !=
  //    0) {
  //  std::cerr << "Failed to set debug flag: " << SDL_GetError() << std::endl;
  //  check = false;
  //}

  SDL_SetHint("SDL_HINT_MOUSE_RELATIVE_WARP_MOTION", "1");

  // Get the attribute to confirm.

  int check2;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &check2);
  check2 == 3
      ? std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION: Set properly, value: "
                  << check2 << std::endl
      : std::cerr << "SDL_GL_CONTEXT_MAJOR_VERSION: Incorrect. \n"
                  << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &check2);
  check2 == 2
      ? std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: Set properly, value: "
                  << check2 << std::endl
      : std::cerr << "SDL_GL_CONTEXT_MINOR_VERSION: Incorrect. \n"
                  << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &check2);
  check2 == 1
      ? std::cout << "SDL_GL_CONTEXT_PROFILE_MASK: Set properly, value: "
                  << check2 << std::endl
      : std::cerr << "SDL_GL_CONTEXT_PROFILE_MASK: Incorrect. \n"
                  << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &check2);
  check2 == 1 ? std::cout << "SDL_GL_ACCELERATED_VISUAL: Set properly, value: "
                          << check2 << std::endl
              : std::cerr << "SDL_GL_ACCELERATED_VISUAL: Incorrect. \n"
                          << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &check2);
  check2 == 1 ? std::cout << "SDL_GL_DOUBLEBUFFER: Set properly, value: "
                          << check2 << std::endl
              : std::cerr << "SDL_GL_DOUBLEBUFFER: Incorrect. \n"
                          << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &check2);
  check2 == 24 ? std::cout << "SDL_GL_DEPTH_SIZE: Set properly, value: "
                           << check2 << std::endl
               : std::cerr << "SDL_GL_DEPTH_SIZE: Incorrect. \n"
                           << check2 << std::endl;
  // Anti-aliasing
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &check2);
  check2 == 1 ? std::cout << "SDL_GL_MULTISAMPLEBUFFERS: Set properly, value: "
                          << check2 << std::endl
              : std::cerr << "SDL_GL_MULTISAMPLEBUFFERS: Incorrect. \n"
                          << check2 << std::endl;
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
  SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &check2);
  check2 == 4 ? std::cout << "SDL_GL_MULTISAMPLESAMPLES: Set properly, value: "
                          << check2 << std::endl
              : std::cerr << "SDL_GL_MULTISAMPLESAMPLES: Incorrect. \n"
                          << check2 << std::endl;

  // Create a window using the given parameters.
  window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, p_w, p_h,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  // Fail if the window did not init.
  if (window == NULL) {
    std::cerr << "Window failed to init, ERROR: " << SDL_GetError()
              << std::endl;
  }

  SDL_GLContext context;
  context = SDL_GL_CreateContext(window);
  // Fail if the context did not init.
  if (context == NULL) {
    std::cerr << "Context failed to init, ERROR: " << SDL_GetError()
              << std::endl;
  }
  gladLoadGLLoader(SDL_GL_GetProcAddress);
  SDL_GL_MakeCurrent(window, context);
  SDL_GL_SetSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize GLAD. ERROR: " << SDL_GetError()
              << std::endl;
    check = false;
  }

  if (check == false) {
    std::cerr << "Something in OpenGL went wrong! ERROR: " << SDL_GetError()
              << std::endl;
    exit(1);
  } else {
    std::cout << "All checks passed!" << std::endl;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  // Fail if the renderer did not init.
  if (renderer == NULL) {
    std::cerr << "Renderer failed to init, ERROR: " << SDL_GetError()
              << std::endl;
  }
}

/**
 * Takes the path of the texture to load.
 *
 * \param p_filePath Path to load the texture.
 *
 */
SDL_Texture *RenderWindow::loadTexture(const char *p_filePath) {

  // Declare the texture variable first as NULL.
  // Then Load the texture in the renderer using the given path.
  // Parameters
  // \param renderer Where to render.
  // \param p_filePath Path to load the texture.
  SDL_Texture *texture = NULL;
  // Load the texture in the renderer using the path given.
  texture = IMG_LoadTexture(renderer, p_filePath);

  // Return an error if something goes wrong.
  if (texture == NULL) {
    std::cerr << "The texture failed to load!! ERROR: " << SDL_GetError()
              << std::endl;
  }

  // Return the texture.
  return texture;
}

void RenderWindow::GLInit() {

  // Stub.
}

// Destroys the window. Used when closing the window.
void RenderWindow::cleanUp() { SDL_DestroyWindow(window); }

// Gets the position of the window.
// Takes the x and y position of the window.
// Returns the position of the window.

// usage of auto before declaring the function.
// auto is used to automatically deduce the type of the variable that is being
// declared. In this case, the type of the variable is std::tuple<int, int>.
// std::tuple is a class that is used to return multiple values from a function.
// In this case, the function returns the x and y position of the window.
// The function returns a tuple of two integers.
// The first integer is the x position of the window.
// The second integer is the y position of the window.
// The function takes two pointers to integers as parameters.
//
int RenderWindow::getWinPos(int *WinPosX, int *WinPosY) {
  SDL_GetWindowPosition(window, WinPosX, WinPosY);
  // return std::make_tuple(*WinPosX, *WinPosY);
  return 0;
}
// Clears the rendered image.
void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::resetSize() { SDL_SetWindowSize(window, 1280, 720); }

void RenderWindow::getWindowSize(int *w, int *h) {
  SDL_GetWindowSize(window, w, h);
}

void RenderWindow::setWindowSize(int w, int h) {
  SDL_SetWindowSize(window, w, h);
}

void RenderWindow::setFullscreen(bool fullscreen) {
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
void RenderWindow::render(Entity &p_entity, int Pos_w, int Pos_h) {
  // Render a rectangle from source. Takes the x, y , w(idth) and h(eight) of
  // the rectangle.
  SDL_Rect src;
  src.x = p_entity.getCurrentFrame().x;
  src.y = p_entity.getCurrentFrame().y;
  src.w = p_entity.getCurrentFrame().w;
  src.h = p_entity.getCurrentFrame().h;

  // Render a rectangle to the destination. Takes the x, y , w(idth) and
  // h(eight) of the rectangle.
  SDL_Rect dst;
  dst.x = p_entity.getPos().x;
  dst.y = p_entity.getPos().y;
  dst.w = p_entity.getCurrentFrame().w * Pos_w;
  dst.h = p_entity.getCurrentFrame().h * Pos_h;

  SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

// Displays the rendered image.
void RenderWindow::display() { SDL_RenderPresent(renderer); }

// Swap the buffers.
void RenderWindow::swap() { SDL_GL_SwapWindow(window); }

void RenderWindow::grabmouse() { SDL_SetRelativeMouseMode(SDL_TRUE); }
void RenderWindow::releasemouse() { SDL_SetRelativeMouseMode(SDL_FALSE); }

// Imgui init
void RenderWindow::ImGuiInit() {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;           // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Setup Platform/Renderer bindings and send error if failed.
  if (!ImGui_ImplSDL2_InitForOpenGL(window, context)) {
    std::cerr << "Failed to init ImGui for OpenGL: " << SDL_GetError()
              << std::endl;
  }

  ImGui_ImplOpenGL3_Init("#version 130");
}

// Imgui render
void RenderWindow::ImGuiRenderStart() {
  // Start the Dear ImGui frame
  // Report errors if failed.
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

// Imgui render finish
void RenderWindow::ImGuiRenderFinish() { ImGui::Render(); }

// Imgui shutdown
void RenderWindow::ImGuiShutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  std::cout << "Shutting down ImGui" << std::endl;
  ImGui::DestroyContext();
}
