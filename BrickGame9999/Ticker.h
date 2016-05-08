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
		{ tickCount = 0; state = !state; }
	bool state = true;

	void setLength(int length)
		{ tickLength = length; }
	int getTickCount()
		{ return tickCount; }

private:
	int tickLength;
	int tickCount = 0;
	
};