// header file for global constants and types

#pragma once

#include <SDL2/SDL.h>
#include "Logger.hpp"
using namespace std;

// BG9999 screen size on monitor
const SDL_Rect scrRect = { 0, 0, 233, 215 };

// BG9999 logical main screen size
const SDL_Rect logicalScreen = { 0, 0, 10, 20 };

// global logger
extern Logger l;
