#include "Device.h"

void Device::nextBG()
{
	setBG(bgIndex + 1);
}

void Device::prevBG()
{
	setBG(bgIndex - 1);
}

void Device::setBG(int i)
{
	if (i >= bgCount)
		i = i % bgCount;

	if (i < 0)
		i = (i + bgCount) % bgCount;

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