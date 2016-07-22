#include "Device.h"

void Device::nextBG()
{
	setBG(bgIndex + 1);
}

void Device::prevBG()
{
	setBG(bgIndex - 1);
}

void Device::setLevel(int level)
{
	if (level > 9)
	{
		this->level = level % 10;
	}
	else if (level < 0)
	{
		this->level = 0;
	}
	else
	{
		this->level = level;
	}
}

void Device::setSpeed(int speed)
{
	if (speed > 9)
	{
		this->speed = 9;
	}
	else if (speed < 0)
	{
		this->speed = 0;
	}
	else
	{
		this->speed = speed;
	}
}

void Device::setBG(int i)
{
	if (i >= bgCount)
	{
		i = i % bgCount;
	}
		

	if (i < 0)
	{
		i = (i + bgCount) % bgCount;
	}

	bgIndex = i;
}

void Device::reset()
{
	lives = 0;
	inGame = false;
	screen.clear();
}

void Device::increaseScore(int amount, char hiScoreLetter)
{
	score += amount;
	if (highScore[hiScoreLetter] < score) highScore[hiScoreLetter] = score;
}