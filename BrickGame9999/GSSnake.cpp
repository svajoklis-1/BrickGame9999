#include "GSSnake.h"

#include <iostream>
using namespace std;

GSSnake::GSSnake(Device &dev, GSSnakeVariant variant) :
foodTicker(20),
snakeTicker(15 - dev.speed),
snakeHeadBlinkTicker(3)
{
	currentVariant = variant;

	if (!dev.inGame)
	{
		dev.score = 0;
		if (variant == GSSNAKE_NORMAL)
		{
			dev.lives = 3;
		}
		else if (variant == GSSNAKE_INFINITE)
		{
			dev.lives = 1;
		}
	}

	if (variant == GSSNAKE_NORMAL)
	{
		highScoreLetter = 'A';
		snakeLengthRequired = 20+3;
	}
	else if (variant == GSSNAKE_INFINITE)
	{
		highScoreLetter = 'B';
		snakeLengthRequired = 999;
	}

	dev.inGame = true;
	
	dev.screen.score.setNumber(dev.score);

	dev.screen.highScore.setNumber(dev.highScore[highScoreLetter]);

	dev.screen.speed.setLink(&dev.speed);
	dev.screen.speed.setLinked();
	dev.screen.level.setLink(&dev.level);
	dev.screen.level.setLinked();

	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();

	dev.screen.hintArray.setCount(dev.lives);

	defineLevels();

	reset(dev);
}

GSSnake::~GSSnake()
{
}

void GSSnake::parseEvent(Device &dev, Key k, KeyState state)
{
	if (state == STATE_DOWN)
	{
		if (!didTurn)
		{
			int old_dir = dir;
			switch (k)
			{
			case KEY_ACTION: break;

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

		if (k == KEY_ACTION)
		{
			speeding = true;
		}
	}
	
	if (state == STATE_UP)
	{
		if (k == KEY_ACTION)
		{
			speeding = false;
		}
	}

	if (speeding)
		snakeTicker.setLength(3);
	else
		snakeTicker.setLength(15 - dev.speed);
}

void GSSnake::tick(Device& dev)
{
	switch (stateSegment)
	{
	case 0:
		tickPause(dev);
		break;
	case 1:
		tickSnake(dev);
		break;
	case 2:
		tickExplosion(dev);
		break;
	}
}

void GSSnake::tickSnake(Device &dev)
{
	/*******************************************   LOGIC   *********************************/
	bool movingOn = false;
	// move snake
	if (snakeTicker.triggered())
	{
		// reset turn protection
		didTurn = false;
		snakeTicker.reset();

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

		// check for collision with itself and walls
		for (int i = 1; i < snakeLength; i++)
		{
			if ((snakeSegments[i] == snakeSegments[0]) || (levels[dev.level % levels.size()][snakeHeadY * 10 + snakeHeadX] != ' '))
			{
				dev.lives--;
				movingOn = true;
				break;
			}
		}

		// check for collision with food
		if (snakeSegments[0] == food)
		{
			dev.score += 10;

			genFood(dev.level);
			snakeLength++;

			if (snakeLength == snakeLengthRequired)
			{
				dev.score += 50;
				dev.level++;
				if (dev.level == 10)
					dev.level = 0;
				dev.speed++;
				if (dev.speed == 10)
					dev.speed = 9;
				reset(dev);
			}
		}

		if (dev.highScore[highScoreLetter] < dev.score)
		{
			dev.highScore[highScoreLetter] = dev.score;
		}
	}
	/*******************************************   TICK   *********************************/
	// logic tick
	snakeTicker.tick();

	if (movingOn)
	{
		explosion.setCoord(snakeSegments[0]);
		gameTick = 0;
		stateSegment++;
	}
}

void GSSnake::tickPause(Device &dev)
{
	if (gameTick >= gameDelay)
		stateSegment++;

	// game tick
	gameTick++;
}

void GSSnake::tickExplosion(Device &dev)
{
	if (gameTick >= gameDelay)
	{
		if (dev.lives == 0)
		{
			nextState = GS_GAMEOVER;
		}
		else
		{
			nextState = GS_GAMEOVER_TOCURRENT;
		}
	}

	gameTick++;
}

void GSSnake::reset(Device &dev)
{
	snakeLength = 3;
	snakeHeadX = 5;
	snakeHeadY = 10;

	snakeSegments[0] = { snakeHeadX, snakeHeadY };
	snakeSegments[1] = { snakeHeadX - 1, snakeHeadY };
	snakeSegments[2] = { snakeHeadX - 2, snakeHeadY };

	genFood(dev.level);

	snakeHeadBlinkTicker.reset();
	snakeTicker.reset();
	gameTick = 0;
	stateSegment = 0;
	dir = RIGHT;

	snakeTicker.setLength(15 - dev.speed);
}

void GSSnake::genFood(int level)
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

			if (levels[level % levels.size()][food.y * 10 + food.x] != ' ')
			{
				collides = true;
			}
		}
	}

	foodTicker.state = true;
}

void GSSnake::render(Device &dev)
{
	/*******************************************   RENDER   *********************************/
	dev.screen.mainArray.clear();
	dev.screen.score.setNumber(dev.score);
	dev.screen.highScore.setNumber(dev.highScore[highScoreLetter]);

	dev.screen.hintArray.clear();
	dev.screen.hintArray.setCount(dev.lives);
	
	dev.screen.level.setLinked();
	dev.screen.speed.setLinked();

	switch (stateSegment)
	{
	case 0:
		renderSnake(dev);
		break;
	case 1:
		renderSnake(dev);
		break;
	case 2:
		renderSnake(dev);
		explosion.render(dev);
		break;
	}
}

void GSSnake::renderSnake(Device &dev)
{
	// blink head
	if (snakeHeadBlinkTicker.triggered())
	{
		snakeHeadBlinkTicker.reset();
	}

	dev.screen.mainArray.copyString(0, 0, levels[dev.level % levels.size()], 10, 20);

	for (int i = 0; i < snakeLength; i++)
	{
		if (i != 0 || snakeHeadBlinkTicker.state == true || speeding)
			dev.screen.mainArray.setPixel(snakeSegments[i], ON);
	}

	// draw food
	if (foodTicker.triggered())
	{
		foodTicker.reset();
	}

	if (foodTicker.state == true)
	{
		dev.screen.mainArray.setPixel(food, ON);
	}

	// display tick
	snakeHeadBlinkTicker.tick();
	foodTicker.tick();
}

void GSSnake::defineLevels()
{
	int level = -1;

	level++; // 0
	levels[level] =
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          ";

	level++; // 1
	levels[level] =
		"          "
		"          "
		"  ******  "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"  ******  "
		"          "
		"          ";

	level++; // 2
	levels[level] =
		"          "
		"          "
		"          "
		"          "
		"          "
		"  ******  "
		"  *    *  "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"  *    *  "
		"  ******  "
		"          "
		"          "
		"          "
		"          "
		"          ";

	level++; // 3
	levels[level] =
		"          "
		" ***  *** "
		" *      * "
		" *      * "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		" *      * "
		" *      * "
		" ***  *** "
		"          ";

	level++; // 4
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";

	level++; // 5
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"          "
		"          "
		"   ****   "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"   ****   "
		"          "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";

	level++; // 6
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"  ******  "
		"  *    *  "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"          "
		"  *    *  "
		"  ******  "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";

	level++; // 7
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"  ******  "
		"  *    *  "
		"          "
		"  ******  "
		"          "
		"          "
		"          "
		"  ******  "
		"          "
		"  *    *  "
		"  ******  "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";

	level++; // 8
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"  ******  "
		"  *    *  "
		"          "
		"  ******  "
		"          "
		"          "
		"          "
		"  ******  "
		"          "
		"  *    *  "
		"  ******  "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";

	level++; // 9
	levels[level] =
		"***    ***"
		"*        *"
		"*        *"
		"          "
		"  ******  "
		"  *    *  "
		"          "
		"  ******  "
		"          "
		"          "
		"          "
		"  ******  "
		"          "
		"  *    *  "
		"  ******  "
		"          "
		"          "
		"*        *"
		"*        *"
		"***    ***";
}