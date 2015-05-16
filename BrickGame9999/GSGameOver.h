#pragma once

#include "GameState.h"
#include "Ticker.h"

using namespace std;

class GSGameOver : public GameState
{
public:
	GSGameOver(Device &dev, GameStates nextState);
	~GSGameOver();
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k, KeyState state) override;
	void render(Device &/*dev*/) override {};

private:
	Ticker lineTicker;
	int lineState = 0;

	void tickCurtain(Device &dev);
	void tickExplosion(Device &dev){ };
	int transitionState = 0;

	GameStates stateAfter;
};