#pragma once

#include "GameState.h"

class GSRain : public GameState
{
public:
	GSRain();
	void tick(Device &dev);
	void parseEvent(Key k);

private:
	int numDrops = 10;
	bool drops[10*20];

	int ticks = 0;
	int rainTicks = 0;

	int frequency = 5;
	int dir = 1;
};