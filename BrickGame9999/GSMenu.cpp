#include "GSMenu.h"

int GSMenu::currentL = 0;

GSMenu::GSMenu(Device &dev)
{
	for (int i = 0; i < letterCount; i++)
	{
		letters[i] = "";
	}

	letters[A].append("  *  ");
	letters[A].append(" * * ");
	letters[A].append("*   *");
	letters[A].append("*****");
	letters[A].append("*   *");
	
	letters[B].append("**** ");
	letters[B].append("*   *");
	letters[B].append("**** ");
	letters[B].append("*   *");
	letters[B].append("**** ");

	letters[C].append(" *** ");
	letters[C].append("*   *");
	letters[C].append("*    ");
	letters[C].append("*   *");
	letters[C].append(" *** ");

	letters[D].append("**** ");
	letters[D].append(" *  *");
	letters[D].append(" *  *");
	letters[D].append(" *  *");
	letters[D].append("**** ");

	letters[E].append("*****");
	letters[E].append("*    ");
	letters[E].append("**** ");
	letters[E].append("*    ");
	letters[E].append("*****");

	letters[G].append(" ****");
	letters[G].append("*    ");
	letters[G].append("* ***");
	letters[G].append("*   *");
	letters[G].append(" *** ");

	letters[R].append("**** ");
	letters[R].append(" *  *");
	letters[R].append(" *  *");
	letters[R].append("**** ");
	letters[R].append(" *  *");

	letters[S].append(" ****");
	letters[S].append("*    ");
	letters[S].append(" *** ");
	letters[S].append("    *");
	letters[S].append("**** ");


	for (int i = 0; i < numCount; i++)
	{
		numbers[i] = "";
	}

	numbers[0].append("***");
	numbers[0].append("* *");
	numbers[0].append("* *");
	numbers[0].append("* *");
	numbers[0].append("***");

	numbers[1].append(" * ");
	numbers[1].append("** ");
	numbers[1].append(" * ");
	numbers[1].append(" * ");
	numbers[1].append("***");

	numbers[2].append("***");
	numbers[2].append("  *");
	numbers[2].append("***");
	numbers[2].append("*  ");
	numbers[2].append("***");

	numbers[3].append("***");
	numbers[3].append("  *");
	numbers[3].append("***");
	numbers[3].append("  *");
	numbers[3].append("***");

	numbers[4].append("* *");
	numbers[4].append("* *");
	numbers[4].append("***");
	numbers[4].append("  *");
	numbers[4].append("  *");

	numbers[5].append("***");
	numbers[5].append("*  ");
	numbers[5].append("***");
	numbers[5].append("  *");
	numbers[5].append("***");

	numbers[6].append("***");
	numbers[6].append("*  ");
	numbers[6].append("***");
	numbers[6].append("* *");
	numbers[6].append("***");

	numbers[7].append("***");
	numbers[7].append("  *");
	numbers[7].append("  *");
	numbers[7].append(" * ");
	numbers[7].append(" * ");

	numbers[8].append("***");
	numbers[8].append("* *");
	numbers[8].append("***");
	numbers[8].append("* *");
	numbers[8].append("***");

	numbers[9].append("***");
	numbers[9].append("* *");
	numbers[9].append("***");
	numbers[9].append("  *");
	numbers[9].append("***");

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

void GSMenu::parseEvent(Device &dev, Key k)
{
	switch (k)
	{
	case KEY_LEFT:
		currentL -= 1;
		if (currentL < 0)
			currentL = letterCount - 1;

		flipState = 1;
		turning = false;
		turnDelayTick = 0;
		flipTick = 0;
		flipDir = 1;
		break;

	case KEY_RIGHT:
		currentL += 1;
		if (currentL >= letterCount)
			currentL = 0;

		flipState = 1;
		turning = false;
		turnDelayTick = 0;
		flipTick = 0;
		flipDir = 1;
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
	dev.screen.mainArray.clear();

	drawLetter(dev);
	drawNumber(dev);
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

		flipTick++;
	}
	else
	{
		turnDelayTick++;

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

	for (int y = 0; y < numberH; y++)
	{
		for (int x = 0; x < numberW; x++)
		{
			if (numbers[singles][y * numberW + x] == '*')
				dev.screen.mainArray.setPixel(x + drawX, y + numberY, ON);
		}
	}

	drawX = numberX;

	for (int y = 0; y < numberH; y++)
	{
		for (int x = 0; x < numberW; x++)
		{
			if (numbers[tens][y * numberW + x] == '*')
				dev.screen.mainArray.setPixel(x + drawX, y + numberY, ON);
		}
	}
}


GSMenu::~GSMenu()
{
}