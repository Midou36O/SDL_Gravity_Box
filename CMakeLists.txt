cmake_minimum_required(VERSION 3.5)
project(SDL_Gravity_Box CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenGL preferences
set(OpenGL_GL_PREFERENCE GLVND)

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# sdl2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# sdl2_mixer
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# glad
include_directories("src/inc/glad")
include_directories("src/inc/KHR")

# include .hpp files
include_directories("src/inc")

# Dear ImGui
include_directories("src/inc/imgui")
include_directories("src/inc/imgui/backends")

file(
  GLOB
  SOURCES
  "src/*.cpp"
  "src/*.c"
  "src/inc/*.hpp"
  "src/inc/glad/glad.h"
  "src/inc/KHR/khrplatform.h"
  "src/inc/imgui/*.cpp")

add_executable(SDL_Gravity_Box ${SOURCES})
# FIXME: OpenGL will only work on linux according to the docs if
# OPENGL_LIBRARIES and OEPNGL_GL_PREFERENCE is set! TODO: Find a way to make
# this portable, hint: use OpenGL::* (This is not explained in detail by Cmake
# Docs so better fix it once I have internet.)
target_link_libraries(
  SDL_Gravity_Box
  PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
          ${OPENGL_LIBRARIES} ${IMGUI_LIBRARIES})
