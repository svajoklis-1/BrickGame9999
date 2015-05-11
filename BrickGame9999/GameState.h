#pragma once

#include "Global.h"
#include "Device.h"

class GameState
{
public:

	virtual void tick(Device &dev) = 0;
	virtual void parseEvent(Device &dev, Key k) = 0;
	virtual void render(Device &dev) = 0;

	GameStates nextState = GS_NONE;

private:

	
};