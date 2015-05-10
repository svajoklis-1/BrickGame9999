#pragma once

#include "Device.h"

enum Key
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ACTION
};

enum GameStates
{
	GS_NONE,
	GS_MENU,
	GS_RAIN,
	GS_SNAKE,
	GS_GAMEOVER,
	GS_GAMEOVER_TOCURRENT
};

class GameState
{
public:

	virtual void tick(Device &dev) = 0;
	virtual void parseEvent(Device &dev, Key k) = 0;
	virtual void render(Device &dev) = 0;

	GameStates nextState = GS_NONE;

private:

	
};