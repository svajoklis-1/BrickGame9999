#pragma once

#include <SDL.h>

// Main class of the simulator

#include "ResourceStore.h"
#include "BackgroundRenderer.h"
#include "ScreenRenderer.h"
#include "Device.h"
#include "GameState.h"
#include "Ticker.h"

class BrickGame
{
public:
	BrickGame();
	~BrickGame();
	void run();

private:
	// Initialization
	void initSystem();
	void deinitSystem();

	void initDevice();

	void configElements();
	void configKeyMap();

	// SDL resource handles

	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Surface *icon;

	int windowScale = 1;
	void setWindowScale(int scale);
	void updateWindowTitle(int gameLoopStartTicks, int gameLoopEndTicks);

	// 0 - nothing, 1 - limit to 250, 2 - vsync
	enum frControl
	{
		FRC_NONE,
		FRC_250,
		FRC_VSYNC
	};

	int framerateControl = FRC_VSYNC;

	// previous keyboard state for keyDown keyUp events

	int prevKeyboardState[KEY_TOTAL];

	// Mapping physical keys to virtual device keys
	int keyMap[KEY_TOTAL];

	// Image and sound resource management

	ResourceStore *res;

	// Virtual BG9999 device

	int lastDeviceTick = 0;
	int deviceTickLength = 60;
	void deviceTick();
	Device *device;

	// Utilities for actuating virtual device

	void render(int ticksBefore);

	BackgroundRenderer *bgRenderer;
	ScreenRenderer *scRenderer;

	SoundPlayer *soundPlayer;

	// Game state management

	GameState *gameState = nullptr;
	GameStates currentState;
	void handleNextGameState(GameStates nextState);
};