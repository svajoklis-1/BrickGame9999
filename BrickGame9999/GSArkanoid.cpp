#include "GSArkanoid.hpp"

namespace GSArkanoid
{
	string State::currentLevel;
	int State::currentCount;

	State::State(Device &dev, Variant variant)
	{
		pauseTicker.setLength(60);
		paddleTicker.setLength(4);
		currentVariant = variant;

		switch (variant)
		{
		case VARIANT_NORMAL:
			highScoreLetter = 'C';
			break;
		case VARIANT_DOUBLE:
			highScoreLetter = 'D';
			break;
		default: 
			l.log(Logger::ERR, "Invalid game variant: %d", variant);
			throw "Invalid game state!";
		}

		defineLevels();

		if (!dev.inGame)
		{
			dev.score = 0;
			dev.lives = 3;
			resetLevel(dev);
		}

		dev.screen.level.setLink(&dev.getLevelRef());
		dev.screen.speed.setLink(&dev.getSpeedRef());
		dev.screen.score.setLink(&dev.score);
		dev.screen.highScore.setLink(&dev.highScore[highScoreLetter]);

		reset(dev);

		dev.inGame = true;
	}

	void State::reset(Device &dev)
	{
		paddleX = 3;
		paddleDX = 0;
		ballX = 5;
		ballY = 18;
		ballDX = 1;
		ballDY = -1;
		slid = false;

		ballSpeed = 10 - dev.getSpeed();
		ballTicker.setLength(ballSpeed);

		stateSegment = 0;

		pauseTicker.reset();
		paddleTicker.reset();
		ballTicker.reset();
	}

	void State::resetLevel(Device &dev)
	{
		currentLevel = levels[dev.getLevel() % levelCount].data;
		currentCount = levels[dev.getLevel() % levelCount].count;
	}

	void State::tick(Device& dev)
	{
		switch (stateSegment)
		{
		case SEG_PAUSE:
			tickPause(dev);
			break;

		case SEG_GAME:
			tickGame(dev);
			break;

		case SEG_EXPLOSION:
			tickExplosion(dev);
			break;

		default: break;
		}
	}

	void State::tickPause(Device &dev)
	{
		if (pauseTicker.triggered())
		{
			pauseTicker.reset();
			stateSegment = SEG_GAME;
			return;
		}

		pauseTicker.tick();
	}

	void State::tickGame(Device &dev)
	{
		if (paddleTicker.triggered())
		{
			paddleTicker.reset();

			if (paddleDX != 0 && ballDY == 1 && ballY == (logicalScreen.h - 2) && (ballX >= paddleX && ballX <= paddleX + paddleW - 1) && !slid)
			{
				ballX += paddleDX;
				if (ballX < 0)
					ballX = 0;
				else if (ballX >= 10)
					ballX = 9;

				ballDY = -ballDY;

				slid = true;

				dev.speaker.playSound(SND_BOUNCE);
			}

			paddleX += paddleDX;
			if (paddleX < 0)
				paddleX = 0;
			if (paddleX > 10 - paddleW)
				paddleX = 10 - paddleW;

		}

		if (ballTicker.triggered())
		{
			ballTicker.reset();
			if (paddleDX != 0 && ballDY == 1 && ballY == (logicalScreen.h - 2) && (ballX >= paddleX && ballX <= paddleX + paddleW - 1) && !slid)
			{
				dev.speaker.playSound(SND_BOUNCE);
				ballX += paddleDX;
				if (ballX < 0)
				{
					ballX = 0;
				}
				else
					if (ballX >= 10)
					{
						ballX = 9;
					}

				ballDY = -ballDY;

				slid = true;
			}
			else
			{
				if (ballX == 9 || ballX == 0)
				{
					ballDX = -ballDX;
				}
				if (ballY == 0 || ballY == 19)
				{
					ballDY = -ballDY;
				}

				// hit detection with paddle
				// block below
				if (ballY == (logicalScreen.h - 2) && (ballX >= paddleX && ballX <= paddleX + paddleW - 1) && (ballDY == 1))
				{
					dev.speaker.playSound(SND_BOUNCE);
					ballDY = -ballDY;
				}
				else // diagonal from left
					if (ballY == (logicalScreen.h - 2) && (ballX == paddleX - 1) && (ballDX == 1) && (ballDY == 1) && !slid)
					{
						dev.speaker.playSound(SND_BOUNCE);
						ballDY = -ballDY;
						ballDX = -ballDX;
					}
					else // diagonal from right
						if (ballY == (logicalScreen.h - 2) && (ballX == paddleX + paddleW) && (ballDX == -1) && (ballDY == 1) && !slid)
						{
							dev.speaker.playSound(SND_BOUNCE);
							ballDY = -ballDY;
							ballDX = -ballDX;
						}

				int newBallDX = ballDX;
				int newBallDY = ballDY;

				bool clearedBlock = false;

				do
				{
					ballDX = newBallDX;
					ballDY = newBallDY;

					// collision with level
					bool collidedWithLevel = false;
					// on y

					if (currentLevel[(ballY + ballDY) * (logicalScreen.w) + ballX] != ' ')
					{
						currentLevel[(ballY + ballDY) * (logicalScreen.w) + ballX] = ' ';
						currentCount--;
						dev.increaseScore(10, highScoreLetter);
						newBallDY = -ballDY;
						collidedWithLevel = true;
						clearedBlock = true;
					}

					if (currentLevel[(ballY) * (logicalScreen.w) + ballX + ballDX] != ' ')
					{
						currentLevel[(ballY) * (logicalScreen.w) + ballX + ballDX] = ' ';
						currentCount--;
						dev.increaseScore(10, highScoreLetter);
						newBallDX = -ballDX;
						collidedWithLevel = true;
						clearedBlock = true;
					}

					// only collide diagonally if clear on vertical/horizontal

					if (!collidedWithLevel && currentLevel[(ballY + ballDY) * (logicalScreen.w) + ballX + ballDX] != ' ')
					{
						currentLevel[(ballY + ballDY) * (logicalScreen.w) + ballX + ballDX] = ' ';
						currentCount--;
						dev.increaseScore(10, highScoreLetter);
						newBallDY = -ballDY;
						newBallDX = -ballDX;
						collidedWithLevel = true;
						clearedBlock = true;
					}

				} while (newBallDX != ballDX || newBallDY != ballDY);

				if (clearedBlock) {
					dev.speaker.playSound(SND_BLIP);
				}

				ballDX = newBallDX;
				ballDY = newBallDY;

				if (ballX + ballDX < 0 || ballX + ballDX >= (logicalScreen.w))
				{
					dev.speaker.playSound(SND_BLIP);
					ballDX = -ballDX;
				}

				if (ballY + ballDY < 0 || ballY + ballDY >= (logicalScreen.h))
				{
					dev.speaker.playSound(SND_BLIP);
					ballDY = -ballDY;
				}

				ballX += ballDX;
				ballY += ballDY;

				slid = false;

				if (currentCount == 0)
				{
					dev.setLevel(dev.getLevel() + 1);
					dev.setSpeed(dev.getSpeed() + 1);

					resetLevel(dev);
					reset(dev);
				}

				if (ballY >= logicalScreen.h)
				{
					dev.pauseable = false;
					dev.lives--;
					explosion.setCoord({ ballX, ballY });
					dev.speaker.playSound(SND_EXPLODE);
					stateSegment = SEG_EXPLOSION;
				}
			}

		}

		paddleTicker.tick();
		ballTicker.tick();
	}

	void State::tickExplosion(Device &dev)
	{
		if (pauseTicker.triggered())
		{
			pauseTicker.reset();
			if (dev.lives > 0)
			{
				nextState = GS_GAMEOVER_TOCURRENT;
				stateSegment = 0;
			}
			else
			{
				nextState = GS_GAMEOVER;
			}

			return;
		}

		pauseTicker.tick();
	}

	void State::parseEvent(Device& dev, Key k, KeyState state)
	{
		if (key_pressed(state))
		{
			switch (k)
			{
			case KEY_LEFT:
				paddleTicker.forceTrigger();
				paddleDX = -1;
				break;
			case KEY_RIGHT:
				paddleTicker.forceTrigger();
				paddleDX = 1;
				break;
			case KEY_ACTION:
				speeding = true;
				break;
			}
		}

		if (key_depressed(state))
		{
			switch (k)
			{
			case KEY_LEFT:
				if (paddleDX == -1) {
					paddleDX = 0;
				}
				break;
			case KEY_RIGHT:
				if (paddleDX == 1) {
					paddleDX = 0;
				}
				break;
			case KEY_ACTION:
				speeding = false;
				break;
			}
		}

		if (speeding)
		{
			ballTicker.setLength(2);
		}
		else
		{
			ballTicker.setLength(this->ballSpeed);
		}
	}

	void State::postEvents(Device &device)
	{
	}

	void State::render(Device& dev)
	{
		dev.screen.mainArray.clear();
		dev.screen.hintArray.setCount(dev.lives);

		dev.screen.level.setLinked();
		dev.screen.speed.setLinked();

		dev.screen.score.setLinked();
		dev.screen.highScore.setLinked();

		switch (stateSegment)
		{
		case SEG_PAUSE:
			renderGame(dev);
			break;
		case SEG_GAME:
			renderGame(dev);
			break;
		case SEG_EXPLOSION:
			renderGame(dev);
			explosion.render(dev);
			break;

		default:
			l.log(Logger::ERR, "Invalid game segment: %d", stateSegment);
			throw "Invalid game state!";
		}
	}

	void State::renderGame(Device& dev)
	{
		string paddle = "**********";

		dev.screen.mainArray.copyString(paddleX, 20 - 1, paddle, paddleW, 1);

		dev.screen.mainArray.setPixel(ballX, ballY, PXARRAY_ON);

		dev.screen.mainArray.copyString(0, 0, currentLevel, 10, 20);
	}


	State::~State()
	{

	}

	int countStarsInData(string data)
	{
		int count = 0;
		for (auto it = data.begin(); it != data.end(); it++)
		{
			if (*it == '*') count++;
		}

		return count;
	}

	void State::defineLevels()
	{
		levels[levelCount].data =
			"          "
			"          "
			"          "
			" ******** "
			"  ******  "
			"  ******  "
			" ******** "
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
		levels[levelCount].count = countStarsInData(levels[levelCount].data);
		levelCount++;

		levels[levelCount].data =
			"          "
			"          "
			" *      * "
			"  *    *  "
			"  ******  "
			" * **** * "
			" ******** "
			"  *    *  "
			"   *  *   "
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
		levels[levelCount].count = countStarsInData(levels[levelCount].data);
		levelCount++;

		levels[levelCount].data =
			"          "
			"          "
			"          "
			" * **** * "
			"  ******  "
			" ******** "
			"    **    "
			"    **    "
			"    **    "
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
		levels[levelCount].count = countStarsInData(levels[levelCount].data);
		levelCount++;

		levels[levelCount].data =
			"          "
			"          "
			"   ****   "
			"  **  **  "
			"  * ** *  "
			"  **  **  "
			"  ******  "
			" ***  *** "
			"  * ** *  "
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
		levels[levelCount].count = countStarsInData(levels[levelCount].data);
		levelCount++;

	}


}
