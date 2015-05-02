#include "GSRain.h"

#include <cstdlib>
#include <ctime>

GSRain::GSRain(Device &dev)
{
	for (int i = 0; i < 10 * 20; i++)
		drops[i] = false;

	drops[0] = true;

	srand((unsigned int)time(0));
}

void GSRain::tick(Device &dev)
{
	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();

	dev.screen.score.setNumber(frequency);
	dev.screen.highScore.setNumber(dir);

	// tick drops
	if (rainTicks >= 3)
	{
		switch (dir)
		{
		case 1:
			// pull down
			for (int y = 20 - 1; y >= 1; y--)
			{
				for (int x = 1; x < 10; x++)
				{
					drops[(y)* 10 + (x)] = drops[(y - 1) * 10 + (x - 1)];
				}
			}

			// fill top row
			for (int i = 0; i < 10; i++)
			{
				drops[i] = (rand() % 100 + 1 <= frequency);
			}

			// fill left clm
			for (int i = 0; i < 20; i++)
			{
				drops[i * 10] = (rand() % 100 + 1 <= frequency);
			}
			break;

		case 0:
			// pull down
			for (int y = 20 - 1; y >= 0; y--)
			{
				for (int x = 0; x < 10; x++)
				{
					drops[(y)* 10 + (x)] = drops[(y - 1) * 10 + (x)];
				}
			}

			// fill top row
			for (int i = 0; i < 10; i++)
			{
				drops[i] = (rand() % 100 + 1 <= frequency);
			}

			break;

		case -1:
			// pull down
			for (int y = 20 - 1; y >= 0; y--)
			{
				for (int x = 0; x < 9; x++)
				{
					drops[(y)* 10 + (x)] = drops[(y - 1) * 10 + (x + 1)];
				}
			}

			// fill top row
			for (int i = 0; i < 10; i++)
			{
				drops[i] = (rand() % 100 + 1 <= frequency);
			}

			// fill left clm
			for (int i = 0; i < 20; i++)
			{
				drops[i * 10 + 9] = (rand() % 100 + 1 <= frequency);
			}
			break;
		}

		
		rainTicks = 0;
	}

	// render drops
	for (int i = 0; i < 10 * 20; i++)
	{
		if (drops[i])
			dev.screen.mainArray.setPixel(i % 10, i / 10, ON);
	}

	// do hint
	if ((ticks / 20) % 2 == 0)
	{
		dev.screen.hintArray.setPixel(0, 0, ON);
		dev.screen.hintArray.setPixel(3, 0, ON);

		dev.screen.hintArray.setPixel(1, 1, ON);
		dev.screen.hintArray.setPixel(2, 1, ON);
		dev.screen.hintArray.setPixel(1, 2, ON);
		dev.screen.hintArray.setPixel(2, 2, ON);

		dev.screen.hintArray.setPixel(0, 3, ON);
		dev.screen.hintArray.setPixel(3, 3, ON);
	}
	else
	{
		dev.screen.hintArray.setPixel(1, 0, ON);
		dev.screen.hintArray.setPixel(2, 0, ON);

		dev.screen.hintArray.setPixel(0, 1, ON);
		dev.screen.hintArray.setPixel(3, 1, ON);
		dev.screen.hintArray.setPixel(0, 2, ON);
		dev.screen.hintArray.setPixel(3, 2, ON);

		dev.screen.hintArray.setPixel(1, 3, ON);
		dev.screen.hintArray.setPixel(2, 3, ON);
	}

	ticks++;
	rainTicks++;
}

void GSRain::parseEvent(Key k)
{
	switch (k)
	{
	case KEY_UP:
		frequency++;
		if (frequency > 100)
			frequency = 100;
		break;

	case KEY_DOWN:
		frequency--;
		if (frequency < 0)
			frequency = 0;
		break;

	case KEY_LEFT:
		dir--;
		if (dir < -1)
			dir = -1;
		break;

	case KEY_RIGHT:
		dir++;
		if (dir > 1)
			dir = 1;
		break;

	case KEY_ACTION:
		nextState = GS_MENU;
		break;
	}
}