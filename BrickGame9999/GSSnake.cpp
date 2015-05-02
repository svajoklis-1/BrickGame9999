#include "GSSnake.h"

#include <iostream>
using namespace std;

GSSnake::GSSnake(Device &dev)
{
	dev.screen.score.setNumber(0);
	dev.screen.highScore.dash();

	dev.score = 0;
	dev.screen.score.setNumber(dev.score);

	dev.highScore = 0;
	dev.screen.highScore.setNumber(dev.highScore);

	dev.screen.speed.setLinked();
	dev.screen.level.setLinked();

	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();


	snakeSegments[0] = { 2, 0 };
	snakeSegments[1] = { 1, 0 };
	snakeSegments[2] = { 0, 0 };
}

GSSnake::~GSSnake()
{
	
}

void GSSnake::parseEvent(Key k)
{
	switch (k)
	{
	case KEY_ACTION:
		nextState = GS_MENU;
		//snakeLength++;
		break;

	case KEY_LEFT:
		dir = LEFT;
		break;

	case KEY_RIGHT:
		dir = RIGHT;
		break;

	case KEY_UP:
		dir = UP;
		break;

	case KEY_DOWN:
		dir = DOWN;
		break;
	}
}

void GSSnake::tick(Device& dev)
{
	if (snakeTick >= snakeTickLength)
	{
		snakeTick = 0;

		// remove last segment
		for (int i = snakeLength - 1; i >= 0; i--)
		{
			snakeSegments[i] = snakeSegments[i - 1];
		}

		// move snake
		switch (dir)
		{
		case LEFT:
			x--;
			if (x < 0)
				x = 9;
			break;

		case UP:
			y--;
			if (y < 0)
				y = 19;
			break;

		case RIGHT:
			x++;
			if (x >= 10)
				x = 0;
			break;

		case DOWN:
			y++;
			if (y >= 20)
				y = 0;
			break;
		}

		snakeSegments[0] = { x, y };
	}

	if (snakeHeadBlinkTick > snakeHeadBlinkTickLength)
	{
		snakeHeadBlinkTick = 0;
		drawHead = !drawHead;
	}

	// draw snake
	dev.screen.mainArray.clear();
	
	for (int i = 0; i < snakeLength; i++)
	{
		if (i != 0 || drawHead)
			dev.screen.mainArray.setPixel(snakeSegments[i].x, snakeSegments[i].y, ON);
	}

	snakeTick++;
	snakeHeadBlinkTick++;
}

