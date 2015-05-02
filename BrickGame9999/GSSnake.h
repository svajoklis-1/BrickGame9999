#pragma once

#include "GameState.h"

#include <string>
using namespace std;

using namespace std;

class GSSnake : public GameState
{
public:
	GSSnake(Device &dev);
	~GSSnake();
	void tick(Device &dev) override;
	void parseEvent(Key k) override;

private:

	struct coord
	{
		int x;
		int y;
	};

	enum dirs
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	coord snakeSegments[256];
	int snakeLength = 3;

	int snakeTickLength = 10;
	int snakeTick = 0;

	int snakeHeadBlinkTickLength = 2;
	int snakeHeadBlinkTick = 0;
	bool drawHead = true;
	
	int x = 2, y = 0;
	int dir = RIGHT;
	
};