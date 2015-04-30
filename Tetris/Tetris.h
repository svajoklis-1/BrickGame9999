#pragma once

#include <SDL.h>
#include <SDL_image.h>

// main class of the simulator

#include "ResourceStore.h"
#include "BackgroundRenderer.h"
#include "Screen.h"
#include "ScreenRenderer.h"
#include "Device.h"

#include "GameState.h"
#include "GSRain.h"
#include "GSMenu.h"

class Tetris
{
public:
	Tetris();
	~Tetris();
	void run();
private:
	ResourceStore *res;

	SDL_Window *w;
	SDL_Renderer *r;

	SDL_Surface *icon;

	BackgroundRenderer *bgRenderer;
	ScreenRenderer *scRenderer;

	Device device;

	GameState *gameState = nullptr;
};