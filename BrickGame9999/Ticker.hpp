#pragma once

class Ticker
{
public:
	Ticker(int length);
	Ticker() = default;


	bool triggered() const;
	void forceTrigger();

	void tick();

	void reset();

	// get current state
	bool getState(int lengthInPeriods) const;

	void setState(bool state, int lengthInPeriods);

	// Set the period length of the ticker
	void setLength(int length);

	// Get how many ticks have passed since the beginning of the current period
	int getTickCount();

	// Get how many periods have passed
	int getPeriodCount() const;

	// Reset period count to 0
	void resetPeriodCount();

private:
	// Length of a single period
	int periodLength;

	// How many ticks have passed since the beginning of the current period
	int tickCount = 0;

	// Count how many times the ticker was reset
	int periodCount = 0;
};