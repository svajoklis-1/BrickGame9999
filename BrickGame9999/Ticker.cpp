#include "Ticker.h"

Ticker::Ticker(int length)
{
	tickLength = length;
};

bool Ticker::triggered()
{
	return tickCount >= tickLength;
}
void Ticker::forceTrigger()
{
	tickCount = tickLength;
}

void Ticker::tick()
{
	tickCount++;
}

void Ticker::reset()
{
	tickCount = 0;
	periodCount += 1;
}

bool Ticker::getState(int periodLength) {
	return periodCount % periodLength == periodLength - 1;
}

void Ticker::setState(bool state, int periodLength)
{
	tickCount = 0;
	if (state)
	{
		if (getState(periodLength))
		{
			return;
		}
		else
		{
			periodCount = int(periodCount / periodLength) * periodLength + periodLength - 1;
		}
	}
	else
	{
		if (!getState(periodLength))
		{
			return;
		}
		else
		{
			periodCount = int(periodCount / periodLength) * periodLength + periodLength;
		}
	}
}

void Ticker::setLength(int length)
{
	tickLength = length;
}
int Ticker::getTickCount()
{
	return tickCount;
}