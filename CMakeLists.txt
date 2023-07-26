cmake_minimum_required(VERSION 3.0)
project(SDL_Gravity_Box CXX)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# sdl2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# sdl2_mixer
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})


# include .hpp files

include_directories(inc)

file(GLOB SOURCES "src/*.cpp" "src/*.h" "inc/*.hpp")

add_executable(SDL_Gravity_Box ${SOURCES})
target_link_libraries(
    SDL_Gravity_Box
	PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
)
