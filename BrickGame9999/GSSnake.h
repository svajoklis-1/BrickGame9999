#pragma once

#include "GameState.h"
#include "Ticker.h"
#include "Explosion.h"

using namespace std;

enum GSSnakeVariant
{
	GSSNAKE_NORMAL,
	GSSNAKE_INFINITE
};

class GSSnake : public GameState
{
public:
	GSSnake(Device &dev, GSSnakeVariant variant);
	~GSSnake();
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k, KeyState state) override;
	void render(Device &dev) override;

private:

	enum dirs
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	GSSnakeVariant currentVariant;
	char highScoreLetter;

	coord snakeSegments[256];
	int snakeLength = 3;
	int snakeLengthRequired;
	bool didTurn = false;
	bool speeding = false;

	Ticker snakeTicker;
	Ticker snakeHeadBlinkTicker;

	coord food;
	void genFood(int level);
	
	int snakeHeadX, snakeHeadY;
	int dir = RIGHT;

	int gameTick = 0;
	const int gameDelay = 60;

	void reset(Device &dev);

	map<int, string> levels;
	void defineLevels();

	Ticker foodTicker;

	int stateSegment = 0;

	void renderSnake(Device &dev);

	void tickSnake(Device &dev);
	void tickPause(Device &dev);
	void tickExplosion(Device &dev);

	Explosion explosion;
};