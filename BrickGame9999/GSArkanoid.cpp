#include "GSArkanoid.hpp"

namespace GSArkanoid
{
	string State::currentLevel;
	int State::currentCount;

	State::State(Device &dev, Variant variant)
	{
		pauseTicker.setLength(60);
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
		b.reset();
		b.setSpeed(dev.getSpeed());

		p.reset();
		
		slid = false;

		stateSegment = 0;

		pauseTicker.reset();
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
		this->p.tick(dev, *this);
		this->b.tick(dev, *this);

		if (currentCount == 0)
		{
			dev.setLevel(dev.getLevel() + 1);
			dev.setSpeed(dev.getSpeed() + 1);

			resetLevel(dev);
			reset(dev);
		}

		if (this->b.getY() >= logicalScreen.h - 1)
		{
			dev.pauseable = false;
			dev.lives--;
			explosion.setCoord({ b.getX(), b.getY() });
			dev.speaker.playSound(SND_EXPLODE);
			stateSegment = SEG_EXPLOSION;
		}
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
				this->directionKeysPressed++;
				this->p.startMoving(-1);
				break;
			case KEY_RIGHT:
				this->directionKeysPressed++;
				this->p.startMoving(1);
				break;
			case KEY_ACTION:
				if (!this->b.isSpeeding())
				{
					this->b.setSpeeding(true);
				}
				break;
			}
		}

		if (key_depressed(state))
		{
			switch (k)
			{
			case KEY_LEFT:
			case KEY_RIGHT:
				this->directionKeysPressed--;
				if (this->directionKeysPressed == 0) {
					this->p.startMoving(0);
				}
				break;

			case KEY_ACTION:
				if (this->b.isSpeeding())
				{
					this->b.setSpeeding(false);
				}
				break;
			}
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

		dev.screen.mainArray.copyString(p.getX(), logicalScreen.h - 1, paddle, p.getW(), 1);

		dev.screen.mainArray.setPixel(b.getX(), b.getY(), PXARRAY_ON);

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

	void State::clearBlock(Device &dev, int location)
	{
		currentLevel[location] = ' ';
		currentCount--;
		dev.increaseScore(10, highScoreLetter);
	}

	bool State::isBlockOccupied(Device &dev, int location)
	{
		return currentLevel[location] != ' ';
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
