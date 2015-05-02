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
	GS_SNAKE
};

class GameState
{
public:

	virtual void tick(Device &dev) = 0;
	virtual void parseEvent(Key k) = 0;

	GameStates nextState = GS_NONE;

private:

	
};