#include "GSMenu.hpp"

namespace GSMenu
{
	int State::currentL = 0;

	State::State(Device &dev) :
		animTicker(60)
	{
		defineGraphics();

		if (!dev.inGame)
			dev.screen.highScore.dash();

		dev.screen.score.dash();
		dev.screen.level.setLink(&dev.getLevelRef());
		dev.screen.level.setLinked();
		dev.screen.speed.setLink(&dev.getSpeedRef());
		dev.screen.speed.setLinked();

		dev.screen.hintArray.clear();

		dev.inGame = false;
	}

	void State::resetAnim()
	{
		flipState = 1;
		turning = false;
		turnDelayTick = 0;
		flipTick = 0;
		flipDir = 1;
		animFrame = 0;
		animTicker.reset();
	}

	void State::parseEvent(Device &dev, Key k, KeyState state)
	{
		if (state == STATE_DOWN)
		{
			int &speed = dev.getSpeedRef();
			int &level = dev.getLevelRef();
			switch (k)
			{
			case KEY_LEFT:
				dev.speaker.playSound(SND_BLIP);
				stage--;
				if (stage < 0)
					stage = 99;
				break;

			case KEY_RIGHT:
				dev.speaker.playSound(SND_BLIP);
				stage++;
				if (stage > 99)
					stage = 0;
				break;

			case KEY_UP:
				dev.speaker.playSound(SND_BLIP);
				speed++;
				if (speed == 10)
					speed = 0;
				break;

			case KEY_DOWN:
				dev.speaker.playSound(SND_BLIP);
				level++;
				if (level == 10)
					level = 0;
				break;

			case KEY_ACTION:
				currentL += 1;
				if (currentL >= letterCount)
					currentL = 0;

				resetAnim();
				break;

			case KEY_START: break;
			case KEY_RESET: break;
			case KEY_TOTAL: break;

			default: break;
			}
		}
		else
		{

		}

	}

	GameStates State::getSelectedState()
	{
		switch (currentL)
		{
		case R:
			return GS_RAIN;
		case A:
			return GS_SNAKE;
		case B:
			return GS_SNAKEINF;
		case C:
			return GS_ARKANOID;
		case D:
			return GS_DEFEND;
		default:
			return GS_NONE;
		}
	}

	void State::tick(Device &/*dev*/)
	{
		if (animTicker.triggered())
		{
			animTicker.reset();

			animFrame++;
			if (animFrame >= 4)
				animFrame = 0;
		}

		animTicker.tick();

		if (turning)
		{
			flipTick++;
		}
		else
		{
			turnDelayTick++;
		}
	}

	void State::drawLetter(Device &dev)
	{
		if (turnDelayTick >= turnDelay)
		{
			turning = true;
			turnDelayTick = 0;
		}

		if (turning)
		{
			if (flipTick >= 5)
			{
				flipState += flipDir;

				if (flipState >= 5)
				{
					flipState = 3;
					flipDir = -flipDir;
				}

				if (flipState <= 0)
				{
					flipState = 1;
					turning = false;
					flipDir = -flipDir;
				}

				flipTick = 0;
			}

			int middle = int(letterW / 2);
			int actualX, actualY;
			for (int y = 0; y < letterH; y++)
			{
				actualY = y;
				if (flipState <= 2)
				{
					for (int x = 0; x < letterW; x++)
					{
						actualX = x;
						if (x < middle)
						{
							if (flipState == 1)
							{
								actualX = actualX + 1;
							}

							if (flipState == 2)
							{
								actualX = middle;
							}
						}

						if (x > middle)
						{
							if (flipState == 1)
							{
								actualX = actualX - 1;
							}

							if (flipState == 2)
							{
								actualX = middle;
							}
						}

						if (letters[currentL][y * letterW + x] == '*')
							dev.screen.mainArray.setPixel(actualX + letterX, actualY + letterY, PXARRAY_ON);
					}
				}
				else
				{
					for (int x = letterW - 1; x >= 0; x--)
					{
						actualX = letterW - 1 - x;

						if (x < middle)
						{
							if (flipState == 3)
							{
								actualX = actualX - 1;
							}
						}

						if (x > middle)
						{
							if (flipState == 3)
							{
								actualX = actualX + 1;
							}
						}

						if (letters[currentL][y * letterW + x] == '*')
							dev.screen.mainArray.setPixel(actualX + letterX, actualY + letterY, PXARRAY_ON);
					}
				}

			}

		}
		else
		{
			for (int y = 0; y < letterH; y++)
			{
				for (int x = 0; x < letterW; x++)
				{
					if (letters[currentL][y * letterW + x] == '*')
						dev.screen.mainArray.setPixel(x + letterX, y + letterY, PXARRAY_ON);
				}

			}
		}
	}

	void State::drawNumber(Device& dev)
	{
		int drawX = numberX + numberW + 1;

		int tens = stage / 10;
		int singles = stage % 10;

		dev.screen.mainArray.copyString(drawX, numberY, numbers[singles], numberW, numberH);

		drawX = numberX;

		dev.screen.mainArray.copyString(drawX, numberY, numbers[tens], numberW, numberH);
	}

	void State::render(Device &dev)
	{
		dev.screen.mainArray.clear();

		dev.screen.level.setLinked();
		dev.screen.speed.setLinked();

		drawLetter(dev);
		drawNumber(dev);

		renderAnim(dev);
	}

	void State::renderAnim(Device &dev)
	{
		if (anims.find(currentL) != anims.end())
			dev.screen.mainArray.copyString(1, 6, anims[currentL][animFrame], animW, animH);
	}


	State::~State()
	{
	}


}
