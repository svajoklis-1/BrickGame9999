#pragma once

#include <SDL.h>

// main class of the simulator

#include "ResourceStore.h"
#include "BackgroundRenderer.h"
#include "ScreenRenderer.h"
#include "Device.h"

#include "GameState.h"

class BrickGame
{
public:
	BrickGame();
	~BrickGame();
	void run();
private:
	enum frControl 
	{
		FRC_NONE,
		FRC_250,
		FRC_VSYNC
	};

	ResourceStore *res;

	SDL_Window *w;
	SDL_Renderer *r;

	SDL_Surface *icon;

	BackgroundRenderer *bgRenderer;
	ScreenRenderer *scRenderer;

	Device device;

	GameState *gameState = nullptr;
	GameStates currentState;

	int windowScale = 1;
	void setWindowScale(int scale);

	// 0 - nothing, 1 - limit to 250, 2 - vsync
	int framerateControl = 2;

	int prevKeyboardState[KEY_TOTAL];
	int keyMap[KEY_TOTAL];
};