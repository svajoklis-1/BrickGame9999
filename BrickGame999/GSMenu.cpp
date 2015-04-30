#include "GSMenu.h"

GSMenu::GSMenu()
{
	for (int i = 0; i < letterC; i++)
	{
		letters[i] = "";
	}

	letters[0].append("  *  ");
	letters[0].append(" * * ");
	letters[0].append("*   *");
	letters[0].append("*****");
	letters[0].append("*   *");

	letters[1].append("**** ");
	letters[1].append("*   *");
	letters[1].append("**** ");
	letters[1].append("*   *");
	letters[1].append("**** ");

	letters[2].append(" *** ");
	letters[2].append("*   *");
	letters[2].append("*    ");
	letters[2].append("*   *");
	letters[2].append(" *** ");

	letters[3].append("**** ");
	letters[3].append("*   *");
	letters[3].append("*   *");
	letters[3].append("*   *");
	letters[3].append("**** ");

	letters[4].append("*****");
	letters[4].append("*    ");
	letters[4].append("*****");
	letters[4].append("*    ");
	letters[4].append("*****");

	letters[5].append("**** ");
	letters[5].append("*   *");
	letters[5].append("*   *");
	letters[5].append("**** ");
	letters[5].append("*   *");
}

void GSMenu::parseEvent(Key k)
{
	switch (k)
	{
	case LEFT:
		currentL -= 1;
		if (currentL < 0)
			currentL = letterC - 1;

		flipState = 1;
		turning = false;
		turnDelayTick = 0;
		flipTick = 0;
		flipDir = 1;
		break;

	case RIGHT:
		currentL += 1;
		if (currentL >= letterC)
			currentL = 0;

		flipState = 1;
		turning = false;
		turnDelayTick = 0;
		flipTick = 0;
		flipDir = 1;
		break;

	case ACTION:
		if (currentL == R)
			nextState = GS_RAIN;
		break;
	}


}

void GSMenu::tick(Device &dev)
{
	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();

	dev.screen.score.setNumber(currentL);

	drawLetter(dev);
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
						dev.screen.mainArray.setPixel(actualX, actualY, ON);
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
						dev.screen.mainArray.setPixel(actualX, actualY, ON);
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
					dev.screen.mainArray.setPixel(x, y, ON);
			}

		}
	}
}

GSMenu::~GSMenu()
{
}