#include "GSSnake.h"

#include <iostream>
using namespace std;

GSSnake::GSSnake(Device &dev)
{
	if (!dev.inGame)
	{
		dev.score = 0;
		dev.lives = 1;
	}

	dev.inGame = true;
	
	dev.screen.score.setNumber(dev.score);

	dev.screen.highScore.setNumber(dev.highScore['S']);

	dev.screen.speed.setLinked();
	dev.screen.level.setLinked();

	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();

	dev.screen.hintArray.setCount(dev.lives);

	reset();
}

GSSnake::~GSSnake()
{
	
}

void GSSnake::parseEvent(Device &dev, Key k)
{
	if (!didTurn)
	{
		int old_dir = dir;
		switch (k)
		{
		case KEY_ACTION:
			//nextState = GS_GAMEOVER_TOCURRENT;
			//snakeLength++;
			//gameRunning = !gameRunning;
			//genFood();
			break;

		case KEY_LEFT:
			if (dir != RIGHT)
				dir = LEFT;
			break;

		case KEY_RIGHT:
			if (dir != LEFT)
				dir = RIGHT;
			break;

		case KEY_UP:
			if (dir != DOWN)
				dir = UP;
			break;

		case KEY_DOWN:
			if (dir != UP)
				dir = DOWN;
			break;
		}
		if (old_dir != dir)
		{
			didTurn = true;
		}
	}
}

void GSSnake::tick(Device& dev)
{
	
	/*******************************************   LOGIC   *********************************/
	
	// move snake
	if (snakeTick >= snakeTickLength)
	{
		// reset turn protection
		didTurn = false;
		snakeTick = 0;

		// remove last segment
		for (int i = snakeLength; i >= 0; i--)
		{
			snakeSegments[i] = snakeSegments[i - 1];
		}

		// move snake
		switch (dir)
		{
		case LEFT:
			snakeHeadX--;
			if (snakeHeadX < 0)
				snakeHeadX = 9;
			break;

		case UP:
			snakeHeadY--;
			if (snakeHeadY < 0)
				snakeHeadY = 19;
			break;

		case RIGHT:
			snakeHeadX++;
			if (snakeHeadX >= 10)
				snakeHeadX = 0;
			break;

		case DOWN:
			snakeHeadY++;
			if (snakeHeadY >= 20)
				snakeHeadY = 0;
			break;
		}

		snakeSegments[0] = { snakeHeadX, snakeHeadY };
	}

	// check for collision with itself
	for (int i = 1; i < snakeLength; i++)
	{
		if (snakeSegments[i] == snakeSegments[0])
		{
			dev.lives--;
			if (dev.lives == 0)
			{
				nextState = GS_GAMEOVER;
			}
			else
			{
				nextState = GS_GAMEOVER_TOCURRENT;
			}
		}
	}

	// check for collision with food
	if (snakeSegments[0] == food)
	{
		dev.score += 10;
		if (dev.highScore['S'] < dev.score)
		{
			dev.highScore['S'] = dev.score;
		}

		genFood();
		snakeLength++;
	}


	/*******************************************   TICK   *********************************/
	// logic tick
	if (gameTick >= gameDelay)
	{
		snakeTick++;
	}

	// game tick
	gameTick++;
}

void GSSnake::reset()
{
	snakeLength = 3;
	snakeHeadX = 2;
	snakeHeadY = 0;

	snakeSegments[0] = { 2, 0 };
	snakeSegments[1] = { 1, 0 };
	snakeSegments[2] = { 0, 0 };

	genFood();
}

void GSSnake::genFood()
{
	bool collides = true;
	while (collides)
	{
		collides = false;

		food.x = rand() % 10;
		food.y = rand() % 20;

		for (int i = 0; i < snakeLength; i++)
		{
			if (food == snakeSegments[i])
			{
				collides = true;
			}
		}
	}
}

void GSSnake::render(Device &dev)
{
	// blink head
	if (snakeHeadBlinkTick >= snakeHeadBlinkTickLength)
	{
		snakeHeadBlinkTick = 0;
		drawBlink = !drawBlink;
	}

	/*******************************************   RENDER   *********************************/
	dev.screen.mainArray.clear();
	dev.screen.score.setNumber(dev.score);
	dev.screen.highScore.setNumber(dev.highScore['S']);

	dev.screen.hintArray.setCount(dev.lives);

	for (int i = 0; i < snakeLength; i++)
	{
		if (i != 0 || drawBlink)
			dev.screen.mainArray.setPixel(snakeSegments[i], ON);
	}

	// draw food
	dev.screen.mainArray.setPixel(food, ON);

	// display tick
	snakeHeadBlinkTick++;
}