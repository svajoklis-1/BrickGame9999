#pragma once

#include "Screen.h"

class Device
{
public:
	Device(int bgCount) : bgCount(bgCount) {};
	Screen screen;

	void reset();

	int score;
	int highScore;
	int level;
	int speed;

	int getCurrentBG(){ return bgIndex; };
	void nextBG();
	void prevBG();
	void setBG(int i);

private:
	int bgCount;
	int bgIndex = 0;
};