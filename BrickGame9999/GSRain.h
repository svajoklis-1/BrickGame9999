#pragma once

#include "GameState.h"
#include "Ticker.h"

class GSRain : public GameState
{
public:
	GSRain(Device &dev);
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k, KeyState state) override;
	void render(Device &/*dev*/) override {};

private:
	int numDrops = 10;
	bool drops[10*20];

	int ticks = 0;
	int rainTicks = 0;

	int dfrequency = 0;
	int frequency = 5;
	int dir = 1;

	Ticker inputTick;
};