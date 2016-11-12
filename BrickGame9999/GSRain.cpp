#include "GSRain.h"

#include <cstdlib>
#include <ctime>

GSRain::GSRain(Device &dev)
{
	this->inputTick = Ticker(60 / 4);

	for (int i = 0; i < 10 * 20; i++)
		this->drops[i] = false;

	this->drops[0] = true;

	srand(static_cast<unsigned int>(time(nullptr)));
}

void GSRain::tick(Device &dev)
{
	dev.screen.mainArray.clear();
	dev.screen.hintArray.clear();

	dev.screen.score.setNumber(this->frequency);
	dev.screen.highScore.setNumber(this->direction);

	// tick drops
	if (this->rainTicks >= 3)
	{
		switch (this->direction)
		{
		case 1:
			this->rainFromLeft();
			break;

		case 0:
			this->rainDown();
			break;

		case -1:
			this->rainFromRight();
			break;
		}
		
		this->rainTicks = 0;
	}

	this->ticks++;
	this->rainTicks++;

	this->inputTick.tick();
	if (this->inputTick.triggered())
	{
		this->inputTick.reset();
		this->onInputTick();
	}
}

void GSRain::onInputTick()
{
	this->frequency += this->dfrequency;
	if (this->frequency > 100)
		this->frequency = 100;
	if (this->frequency < 0)
		this->frequency = 0;
}

void GSRain::rainDown()
{
	// pull down
	for (int y = 20 - 1; y >= 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			this->drops[(y)* 10 + (x)] = this->drops[(y - 1) * 10 + (x)];
		}
	}

	// fill top row
	for (int i = 0; i < 10; i++)
	{
		this->drops[i] = (rand() % 100 + 1 <= this->frequency);
	}
}

void GSRain::rainFromLeft()
{
	// pull down
	for (int y = 20 - 1; y >= 1; y--)
	{
		for (int x = 1; x < 10; x++)
		{
			this->drops[(y)* 10 + (x)] = drops[(y - 1) * 10 + (x - 1)];
		}
	}

	// fill top row
	for (int i = 0; i < 10; i++)
	{
		this->drops[i] = (rand() % 100 + 1 <= this->frequency);
	}

	// fill left clm
	for (int i = 0; i < 20; i++)
	{
		this->drops[i * 10] = (rand() % 100 + 1 <= this->frequency);
	}
}

void GSRain::rainFromRight()
{
	// pull down
	for (int y = 20 - 1; y >= 0; y--)
	{
		for (int x = 0; x < 9; x++)
		{
			this->drops[(y)* 10 + (x)] = this->drops[(y - 1) * 10 + (x + 1)];
		}
	}

	// fill top row
	for (int i = 0; i < 10; i++)
	{
		this->drops[i] = (rand() % 100 + 1 <= this->frequency);
	}

	// fill right column
	for (int i = 0; i < 20; i++)
	{
		this->drops[i * 10 + 9] = (rand() % 100 + 1 <= this->frequency);
	}
}

void GSRain::render(Device &dev)
{
	// render drops
	for (int i = 0; i < 10 * 20; i++)
	{
		if (this->drops[i])
		{
			dev.screen.mainArray.setPixel(i % 10, i / 10, PXARRAY_ON);
		}
	}

	// do hint
	if ((this->ticks / 20) % 2 == 0)
	{
		dev.screen.hintArray.setPixel(0, 0, PXARRAY_ON);
		dev.screen.hintArray.setPixel(3, 0, PXARRAY_ON);

		dev.screen.hintArray.setPixel(1, 1, PXARRAY_ON);
		dev.screen.hintArray.setPixel(2, 1, PXARRAY_ON);
		dev.screen.hintArray.setPixel(1, 2, PXARRAY_ON);
		dev.screen.hintArray.setPixel(2, 2, PXARRAY_ON);

		dev.screen.hintArray.setPixel(0, 3, PXARRAY_ON);
		dev.screen.hintArray.setPixel(3, 3, PXARRAY_ON);
	}
	else
	{
		dev.screen.hintArray.setPixel(1, 0, PXARRAY_ON);
		dev.screen.hintArray.setPixel(2, 0, PXARRAY_ON);

		dev.screen.hintArray.setPixel(0, 1, PXARRAY_ON);
		dev.screen.hintArray.setPixel(3, 1, PXARRAY_ON);
		dev.screen.hintArray.setPixel(0, 2, PXARRAY_ON);
		dev.screen.hintArray.setPixel(3, 2, PXARRAY_ON);

		dev.screen.hintArray.setPixel(1, 3, PXARRAY_ON);
		dev.screen.hintArray.setPixel(2, 3, PXARRAY_ON);
	}
}

void GSRain::parseEvent(Device &dev, Key k, KeyState state)
{
	if (state == STATE_DOWN)
	{
		switch (k)
		{
		case KEY_UP:
			this->dfrequency = 1;
			this->inputTick.forceTrigger();
			break;

		case KEY_DOWN:
			this->inputTick.forceTrigger();
			this->dfrequency = -1;
			break;

		case KEY_LEFT:
			this->direction--;
			if (this->direction < -1)
				this->direction = -1;
			break;

		case KEY_RIGHT:
			this->direction++;
			if (this->direction > 1)
				this->direction = 1;
			break;

		case KEY_ACTION:
			this->nextState = GS_MENU;
			break;

		case KEY_START: break;
		case KEY_RESET: break;
		case KEY_TOTAL: break;
		default: break;
		}
	}
	else if (state == STATE_UP)
	{
		switch (k)
		{
		case KEY_UP: 
		case KEY_DOWN: 
			this->dfrequency = 0;
			break;
		case KEY_LEFT: break;
		case KEY_RIGHT: break;
		case KEY_ACTION: break;
		case KEY_START: break;
		case KEY_RESET: break;
		case KEY_TOTAL: break;
		default: break;
		}
	}

}