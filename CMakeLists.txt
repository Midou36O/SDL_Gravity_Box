cmake_minimum_required(VERSION 3.5)
project(SDL_Gravity_Box CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Choose the type of build, options are: None Debug Release"
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

link_directories(${CMAKE_SOURCE_DIR}/lib)

# OpenGL preferences
set(OpenGL_GL_PREFERENCE GLVND)

# glm
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2 included at ${SDL2_INCLUDE_DIRS}")
# This is a hack since Dear ImGUi strictly asks for the SDL.h file and not the
# directory containing it.
include_directories("/usr/local/include/SDL2")

# sdl2_mixer
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
message(STATUS "SDL2_mixer included at ${SDL2_MIXER_INCLUDE_DIRS}")

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIR}")

if(WIN32)
  set(LIBS SDL2 SDL2_mixer OpenGL glm)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
  set(LIBS SDL2 SDL2_mixer OpenGL glm)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
  # find_package(OpenGL REQUIRED) add_definitions(-DGL_GLEXT_PROTOTYPES)
  set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
else()
  message(FATAL_ERROR "Unsupported platform")
endif(WIN32)
# static image

# add_library(stb_image "src/stb_image.cpp")

# glad
add_library(glad "src/glad.c")
# include_directories("src/inc/glad") include_directories("src/inc/KHR")

# include .hpp files
include_directories("src/inc")

# Dear ImGui
include_directories("src/inc/submodules/imgui")
include_directories("src/inc/submodules/imgui/backends")

file(
  GLOB
  SOURCES
  "src/*.cpp"
  "src/*.c"
  "src/inc/*.hpp"
  "src/inc/glad/glad.h"
  "src/inc/KHR/khrplatform.h"
  "src/inc/submodules/imgui/*.cpp")
add_executable(SDL_Gravity_Box ${SOURCES})
# FIXME: OpenGL will only work on linux according to the docs if
# OPENGL_LIBRARIES and OEPNGL_GL_PREFERENCE is set! TODO: Find a way to make
# this portable, hint: use OpenGL::* (This is not explained in detail by Cmake
# Docs so better fix it once I have internet.)
target_link_libraries(
  SDL_Gravity_Box
  PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
          ${OPENGL_LIBRARIES} ${IMGUI_LIBRARIES})
