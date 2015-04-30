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
	void tick(Device &dev);
	void parseEvent(Key k);

private:
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

	int letterC = 6;
	int letterW = 5;
	int letterH = 5;

	int currentL = 0;

	void drawLetter(Device &dev);

	int flipTick = 0;
	int flipState = 1;
	int flipDir = 1;
	int turnDelay = 60;
	int turnDelayTick = 0;
	bool turning = false;
};