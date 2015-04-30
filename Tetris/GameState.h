#pragma once

#include "Device.h"

enum Key
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ACTION
};

enum GameStates
{
	GS_NONE,
	GS_MENU,
	GS_RAIN
};

class GameState
{
public:

	virtual void tick(Device &dev) = 0;
	virtual void parseEvent(Key k) = 0;

	GameStates nextState = GS_NONE;

private:

	
};