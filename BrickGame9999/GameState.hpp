#pragma once

#include "Global.hpp"
#include "Device.hpp"

class GameState
{
public:
	virtual void tick(Device &dev) = 0;
	virtual void parseEvent(Device &dev, Key k, KeyState state) = 0;
	virtual void postEvents(Device &dev) {};
	virtual void render(Device &dev) = 0;

	virtual ~GameState() {};

	GameStates nextState = GS_NONE;

private:

	
};