[![DeepSource](https://app.deepsource.com/gh/Midou36O/SDL_Gravity_Box.svg/?label=active+issues&show_trend=true&token=Yy5RIIW9uK5rZ9k4pbAxcxr_)](https://app.deepsource.com/gh/Midou36O/SDL_Gravity_Box/?ref=repository-badge)

# SDL_Gravity_Box
Making a "windowed" 2D box that makes the ball move when moving the window (just like an actual box in real life!)

# Video preview

https://user-images.githubusercontent.com/45198486/232357499-e36501e6-2c02-4c14-8fd2-1bdebf58ee01.mp4

# Why do i make this
Because i absolutely fucking hate myself and i have to make something like that for a game (not free) i'm planning to code after exams.

# How do i compile it !11!1!1!1!1!1

## Windows (CMake)

Get Visual Studio 2022 (with C++ Development selected in the installer, of course) and vcpkg. With vcpkg installed, run ``vcpkg install sdl2``, ``vcpkg install sdl2-image`` (it's possible you might have to pass ``--triplet x64-windows``). Then integrate it with Visual Studio 2022 by running ``vcpkg integrate install``. 

Create a new folder called "build" and change directory into it: ``mkdir build; cd build``. 

To use vcpkg packages with CMake, run ``cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake``. You can then build with ``cmake --build .``.

Copy the ``res/img`` directory to the ``build/Debug`` folder. The executable files for this project is in that folder.

## Linux (CMake)

Install SDL2 and SDL2_image development libraries from your distribution's package manager. Use a search engine to find the package names for these.

Create a new folder called "build" and change directory into it: ``mkdir build; cd build``.

Generate build files with ``cmake ..``. You can then build with ``cmake --build .``. 

Copy the ``res/img`` directory to the ``build`` folder. The executable files for this project is in that folder.

## Linux (Make/G++)

[Look here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)

or simply run this

``` g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -I inc && g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image && ./bin/debug/main ```


_**Just consider this repo a sandbox for shit i make lol**_





