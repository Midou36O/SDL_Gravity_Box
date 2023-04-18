#pragma once
#include <SDL2/SDL.h>

 // Enum, basically does ```const int Val = n``` Where n increments every time a new value is declared, n = {0,1,2,3,....,n+1}.
enum KeyPress {
  KBD_DFLT, //Default
  KBD_UP,   // Up
  KBD_DOWN, // Down
  KBD_LEFT, // Left
  KBD_RIGHT, // Right
  KBD_TOT // Total
};



