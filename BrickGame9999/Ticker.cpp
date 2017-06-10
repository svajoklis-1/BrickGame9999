#include "Ticker.hpp"

Ticker::Ticker(int length)
{
	periodLength = length;
};

bool Ticker::triggered() const
{
	return tickCount >= periodLength;
}
void Ticker::forceTrigger()
{
	tickCount = periodLength;
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

int Ticker::getPeriodCount() const
{
	return this->periodCount;
}

void Ticker::resetPeriodCount()
{
	this->periodCount = 0;
}


bool Ticker::getState(int lengthInPeriods) const {
	return periodCount % lengthInPeriods == lengthInPeriods - 1;
}

void Ticker::setState(bool state, int lengthInPeriods)
{
	tickCount = 0;
	if (state)
	{
		if (getState(lengthInPeriods))
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
		if (!getState(lengthInPeriods))
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
	periodLength = length;
}

int Ticker::getTickCount()
{
	return tickCount;
}