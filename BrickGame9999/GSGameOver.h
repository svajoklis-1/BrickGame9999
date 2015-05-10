#pragma once

#include "GameState.h"

#include <string>
using namespace std;

class GSGameOver : public GameState
{
public:
	GSGameOver(Device &dev, GameStates nextState);
	~GSGameOver();
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k) override;

private:
	int tickStep = 3;
	int tickCounter = 0;
	int lineState = 0;

	GameStates stateAfter;
};