#pragma once

class Ticker
{
public:
	Ticker(int length)
		{ tickLength = length; };
	Ticker() = default;

	bool triggered()
		{ return tickCount >= tickLength; }
	void forceTrigger() 
		{ tickCount = tickLength; }

	void tick()
		{ tickCount++; }

	void reset()
	{
		tickCount = 0;
		periodCount += 1;
	}

	bool getState(int periodLength) {
		return periodCount % periodLength == 0;
	}

	void setState(bool state, int periodLength)
	{
		tickCount = 0;
		if (state)
		{
			if (periodCount % periodLength != 0) {
				periodCount = int(periodCount / periodLength) * periodLength + periodLength;
			}
		}
		else
		{
			if (periodCount % periodLength == 0) {
				periodCount += 1;
			}
			else
			{
				periodCount = int(periodCount / periodLength) * periodLength + periodLength + 1;
			}
		}
	}

	void setLength(int length)
		{ tickLength = length; }
	int getTickCount()
		{ return tickCount; }

private:
	int tickLength;
	int tickCount = 0;
	int periodCount = 0;
};