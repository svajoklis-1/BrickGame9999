#pragma once

class Ticker
{
public:
	Ticker(int length){ tickLength = length; };
	bool triggered(){ return tickCount >= tickLength; }
	void tick(){ tickCount++; }
	void reset(){ tickCount = 0; }

private:
	int tickLength;
	int tickCount = 0;
};