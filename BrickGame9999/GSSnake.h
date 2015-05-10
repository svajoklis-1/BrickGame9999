#pragma once

#include "GameState.h"
#include "Types.h"
#include <string>
using namespace std;

using namespace std;

class GSSnake : public GameState
{
public:
	GSSnake(Device &dev);
	~GSSnake();
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k) override;
	void render(Device &dev) override;

private:

	enum dirs
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	coord snakeSegments[256];
	int snakeLength = 3;
	bool didTurn = false;

	int snakeTickLength = 10;
	int snakeTick = 0;

	int snakeHeadBlinkTickLength = 3;
	int snakeHeadBlinkTick = 0;
	bool drawBlink = true;

	coord food;
	void genFood();
	
	int snakeHeadX = 2, snakeHeadY = 0;
	int dir = RIGHT;

	int gameTick = 0;
	const int gameDelay = 60;

	void reset();
	
};