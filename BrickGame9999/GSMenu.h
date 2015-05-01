#pragma once

#include "GameState.h"

#include <string>
using namespace std;

using namespace std;

class GSMenu : public GameState
{
public:
	GSMenu();
	~GSMenu();
	void tick(Device &dev) override;
	void parseEvent(Key k) override;

private:

	// numbers
	string numbers[10];
	int numCount = 10;
	int currentNumber = 0;
	const int numberH = 5;
	const int numberW = 3;
	const int numberX = 1;
	const int numberY = 15;

	void drawNumber(Device &dev);

	// letter related stuffs
	string letters[6];

	enum letters
	{
		A = 0,
		B,
		C,
		D,
		E,
		R
	};

	const int letterX = 2;
	const int letterY = 0;
	const int letterCount = 6;
	const int letterW = 5;
	const int letterH = 5;

	int currentL = 0;

	void drawLetter(Device &dev);

	int flipTick = 0;
	int flipState = 1;
	int flipDir = 1;
	const int turnDelay = 60;
	int turnDelayTick = 0;
	bool turning = false;
};