#include "GSMenu.h"

int GSMenu::currentL = 0;

GSMenu::GSMenu(Device &dev) :
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

	/*string square =
		"****"
		"*  *"
		"*  *"
		"****";

	dev.screen.hintArray.copyString(0, 0, square, 4, 4);*/

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

void GSMenu::parseEvent(Device &dev, Key k, KeyState state)
{
	if (state == STATE_DOWN)
	{
		int &speed = dev.getSpeedRef();
		int &level = dev.getLevelRef();
		switch (k)
		{
		case KEY_LEFT:
			speed--;
			if (speed == -1)
				speed = 9;
			break;

		case KEY_RIGHT:
			speed++;
			if (speed == 10)
				speed = 0;
			break;

		case KEY_UP:
			level++;
			if (level == 10)
				level = 0;
			break;

		case KEY_DOWN:
			level--;
			if (level == -1)
				level = 9;
			break;

		case KEY_ACTION:
			currentL += 1;
			if (currentL >= letterCount)
			currentL = 0;

			resetAnim();
			break;

		case KEY_START: break;
		case KEY_SOUND: break;
		case KEY_RESET: break;
		case KEY_TOTAL: break;

		default: break;
		}
	}
	else
	{
		
	}

}

GameStates GSMenu::getSelectedState()
{
	if (currentL == R)
		return GS_RAIN;
	if (currentL == A)
		return GS_SNAKE;
	if (currentL == B)
		return GS_SNAKEINF;
	if (currentL == C)
		return GS_ARKANOID;

	return GS_NONE;
}

void GSMenu::tick(Device &/*dev*/)
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

	dev.screen.level.setLinked();
	dev.screen.speed.setLinked();

	drawLetter(dev);
	drawNumber(dev);

	renderAnim(dev);
}

void GSMenu::renderAnim(Device &dev)
{
	if (anims.find(currentL) != anims.end())
		dev.screen.mainArray.copyString(1, 6, anims[currentL][animFrame], animW, animH);
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

	letters[R] =
		"**** "
		" *  *"
		" *  *"
		"**** "
		" *  *";

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


	anims[A][0] =
		"        "
		"    *   "
		"        "
		"        "
		"   *    "
		"   *    "
		" ***    "
		"*****   ";

	anims[A][1] =
		"        "
		"    *   "
		"        "
		"        "
		"   **   "
		"   **   "
		" ****   "
		"   **   ";

	anims[A][2] =
		"        "
		"   **   "
		"    *   "
		"    *   "
		"   **   "
		"   **   "
		" ***    "
		"        ";

	anims[A][3] =
		"        "
		" ****   "
		" *  *   "
		"        "
		"   *    "
		"   *    "
		" ***    "
		"        ";



	anims[B][0] =
		"        "
		"    *   "
		"        "
		"        "
		"        "
		"        "
		"        "
		"*****   ";

	anims[B][1] =
		"        "
		"    *   "
		"        "
		"        "
		"    *   "
		"    *   "
		"    *   "
		"   **   ";

	anims[B][2] =
		"        "
		"   **   "
		"    *   "
		"    *   "
		"    *   "
		"    *   "
		"        "
		"        ";
	
	anims[B][3] =
		"        "
		"   **   "
		"   **   "
		"   *    "
		"   *    "
		"        "
		"        "
		"        ";

	anims[C][0] =
		"        "
		" ****** "
		" ****** "
		" ****** "
		"        "
		"        "
		"   *    "
		" ****   ";

	anims[C][1] =
		"        "
		" ****** "
		" ****** "
		" **** * "
		"     *  "
		"        "
		"        "
		"  ****  ";

	anims[C][2] =
		"        "
		" ****** "
		" ****** "
		" **** * "
		"        "
		"        "
		"       *"
		"    ****";

	anims[C][3] =
		"        "
		" ****** "
		" ****** "
		" **** * "
		"     *  "
		"        "
		"        "
		"    ****";


	anims[R][0] =
		"  *   * "
		" *  *   "
		"   *    "
		" *   *  "
		"  *     "
		"     *  "
		"   *    "
		" *    * ";

	anims[R][1] =
		"     *  "
		"*  *   *"
		"  *  *  "
		"*   *   "
		"  *   * "
		"   *    "
		"*     * "
		"    *   ";

	anims[R][2] =
		"  *  *  "
		"      * "
		" *  *   "
		"   *  * "
		" *   *  "
		"   *   *"
		"*   *   "
		" *     *";

	anims[R][3] =
		"*    *  "
		"   *  * "
		"*      *"
		"  *  *  "
		"    *  *"
		"  *   * "
		"*   *   "
		" *   *  ";
}