[![DeepSource](https://app.deepsource.com/gh/Midou36O/SDL_Gravity_Box.svg/?label=active+issues&show_trend=true&token=Yy5RIIW9uK5rZ9k4pbAxcxr_)](https://app.deepsource.com/gh/Midou36O/SDL_Gravity_Box/?ref=repository-badge)

# SDL_Gravity_Box

Making a "windowed" 2D box that makes the ball move when moving the window (just like an actual box in real life!)

# Preview

![Preview](resources/prev.gif)

# Controls (hardcoded)

```
  z    |        up
q s d  | left down right

r: resets the window and position of the characters.
space: pause | play the music.
a: quit.
k: resize to 1080p.
f: full screen.
scroll wheel: increase / decrease speed.
```

# Why do i make this

Because i absolutely fucking hate myself and i have to make something like that for a game (not free) i'm planning to code after exams.

# How do i compile it !11!1!1!1!1!1

## Windows (CMake)

Get Visual Studio 2022 (with C++ Development selected in the installer, of course) and vcpkg. With vcpkg installed, run `vcpkg install sdl2`, `vcpkg install sdl2-image` (it's possible you might have to pass `--triplet x64-windows`). Then integrate it with Visual Studio 2022 by running `vcpkg integrate install`.

Create a new folder called "build" and change directory into it: `mkdir build; cd build`.

To use vcpkg packages with CMake, run `cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`. You can then build with `cmake --build .`.

Copy the `res/img` directory to the `build/Debug` folder. The executable files for this project is in that folder.

## Linux (CMake)

Install SDL2 and SDL2_image development libraries from your distribution's package manager. Use a search engine to find the package names for these.

Create a new folder called "build" and change directory into it: `mkdir build; cd build`.

Generate build files with `cmake ..`. You can then build with `cmake --build .`.

Copy the `res/img` directory to the `build` folder. The executable files for this project is in that folder.

## Linux (Make/G++)

[Look here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)

or simply run this

`g++ -c src/*.cpp src/*.c src/vertx/*.cpp src/inc/submodules/imgui/imgui*.cpp src/inc/submodules/imgui/backends/imgui_impl_sdl2.cpp src/inc/submodules/imgui/backends/imgui_impl_opengl3.cpp -std=c++14 -m64 -g -Wall -I src/inc -I src/inc/submodules/imgui/ -I src/inc/submodules/imgui/backends/ -I /usr/include/SDL2 && g++ *.o -o bin/debug/main -lGL -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -limgui`

(I should look into CMake this is getting unmanageable.)

(NOTE: running gdb will require you to type `run` to run the program, remove gdb if you don't want to debug the program.)

_**Just consider this repo a sandbox for shit i make lol**_
