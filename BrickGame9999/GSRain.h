#pragma once

#include "GameState.h"

class GSRain : public GameState
{
public:
	GSRain(Device &dev);
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k) override;

private:
	int numDrops = 10;
	bool drops[10*20];

	int ticks = 0;
	int rainTicks = 0;

	int frequency = 5;
	int dir = 1;
};