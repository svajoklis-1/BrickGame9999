#include "GSMenu.h"

int GSMenu::currentL = 0;

GSMenu::GSMenu(Device &dev) :
animTicker(60)
{
	defineGraphics();

	if (!dev.inGame)
		dev.screen.highScore.dash();

	dev.screen.score.dash();
	dev.screen.level.dash();
	dev.screen.speed.dash();

	dev.screen.hintArray.clear();

	dev.screen.hintArray.setPixel(0, 0, ON);
	dev.screen.hintArray.setPixel(1, 0, ON);
	dev.screen.hintArray.setPixel(2, 0, ON);
	dev.screen.hintArray.setPixel(3, 0, ON);

	dev.screen.hintArray.setPixel(0, 1, ON);
	dev.screen.hintArray.setPixel(3, 1, ON);

	dev.screen.hintArray.setPixel(0, 2, ON);
	dev.screen.hintArray.setPixel(3, 2, ON);

	dev.screen.hintArray.setPixel(0, 3, ON);
	dev.screen.hintArray.setPixel(1, 3, ON);
	dev.screen.hintArray.setPixel(2, 3, ON);
	dev.screen.hintArray.setPixel(3, 3, ON);

	dev.inGame = false;
}

void GSMenu::resetAnim()
{
	flipState = 1;
	turning = false;
	turnDelayTick = 0;
	flipTick = 0;
	flipDir = 1;
	animFrame = 0;
	animTicker.reset();
}

void GSMenu::parseEvent(Device &dev, Key k)
{
	switch (k)
	{
	case KEY_LEFT:
		currentL -= 1;
		if (currentL < 0)
			currentL = letterCount - 1;

		resetAnim();
		break;

	case KEY_RIGHT:
		currentL += 1;
		if (currentL >= letterCount)
			currentL = 0;

		resetAnim();
		break;
	
	case KEY_UP:
		dev.stage++;
		if (dev.stage >= 100)
			dev.stage = 0;
		break;

	case KEY_DOWN:
		dev.stage--;
		if (dev.stage < 0)
			dev.stage = 99;
		break;

	case KEY_ACTION:
		if (currentL == R)
			nextState = GS_RAIN;
		if (currentL == S)
			nextState = GS_SNAKE;
		if (currentL == G)
			nextState = GS_GAMEOVER;
		break;
	}
}

void GSMenu::tick(Device &dev)
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

void GSMenu::drawLetter(Device &dev)
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
		int actualX = 0, actualY = 0;
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
						dev.screen.mainArray.setPixel(actualX + letterX, actualY + letterY, ON);
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
						dev.screen.mainArray.setPixel(actualX + letterX, actualY + letterY, ON);
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
					dev.screen.mainArray.setPixel(x + letterX, y + letterY, ON);
			}

		}
	}
}

void GSMenu::drawNumber(Device& dev)
{
	int drawX = numberX + numberW + 1;

	int tens = dev.stage / 10;
	int singles = dev.stage % 10;

	dev.screen.mainArray.copyString(drawX, numberY, numbers[singles], numberW, numberH);

	drawX = numberX;

	dev.screen.mainArray.copyString(drawX, numberY, numbers[tens], numberW, numberH);
}

void GSMenu::render(Device &dev)
{
	dev.screen.mainArray.clear();

	dev.screen.score.setNumber(animFrame);

	drawLetter(dev);
	drawNumber(dev);

	renderAnim(dev);
}

void GSMenu::renderAnim(Device &dev)
{
	if (anims.find(currentL) != anims.end())
		dev.screen.mainArray.copyString(1, 5, anims[currentL][animFrame], animW, animH);
}


GSMenu::~GSMenu()
{
}

void GSMenu::defineGraphics()
{
	for (int i = 0; i < letterCount; i++)
	{
		letters[i] = "";
	}

	letters[A] =
		"  *  "
		" * * "
		"*   *"
		"*****"
		"*   *";

	letters[B] =
		"**** "
		"*   *"
		"**** "
		"*   *"
		"**** ";

	letters[C] =
		" *** "
		"*   *"
		"*    "
		"*   *"
		" *** ";

	letters[D] =
		"**** "
		" *  *"
		" *  *"
		" *  *"
		"**** ";

	letters[E] =
		"*****"
		"*    "
		"**** "
		"*    "
		"*****";

	letters[G] =
		" ****"
		"*    "
		"* ***"
		"*   *"
		" *** ";

	letters[R] =
		"**** "
		" *  *"
		" *  *"
		"**** "
		" *  *";

	letters[S] =
		" ****"
		"*    "
		" *** "
		"    *"
		"**** ";


	for (int i = 0; i < numCount; i++)
	{
		numbers[i] = "";
	}

	numbers[0] =
		"***"
		"* *"
		"* *"
		"* *"
		"***";

	numbers[1] =
		" * "
		"** "
		" * "
		" * "
		"***";

	numbers[2] =
		"***"
		"  *"
		"***"
		"*  "
		"***";

	numbers[3] =
		"***"
		"  *"
		"***"
		"  *"
		"***";

	numbers[4] =
		"* *"
		"* *"
		"***"
		"  *"
		"  *";

	numbers[5] =
		"***"
		"*  "
		"***"
		"  *"
		"***";

	numbers[6] =
		"***"
		"*  "
		"***"
		"* *"
		"***";

	numbers[7] =
		"***"
		"  *"
		"  *"
		" * "
		" * ";

	numbers[8] =
		"***"
		"* *"
		"***"
		"* *"
		"***";

	numbers[9] =
		"***"
		"* *"
		"***"
		"  *"
		"***";

	anims[S][0] =
		"        "
		"    *   "
		"        "
		"        "
		"        "
		"        "
		"        "
		"*****   ";

	anims[S][1] =
		"        "
		"    *   "
		"        "
		"        "
		"    *   "
		"    *   "
		"    *   "
		"   **   ";

	anims[S][2] =
		"        "
		"   **   "
		"    *   "
		"    *   "
		"    *   "
		"    *   "
		"        "
		"        ";

	anims[S][3] =
		"        "
		"   **   "
		"   **   "
		"   *    "
		"   *    "
		"        "
		"        "
		"        ";
}