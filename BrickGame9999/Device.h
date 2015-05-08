#pragma once

#include "Screen.h"

class Device
{
public:
	Device(int bgCount) : bgCount(bgCount) {};
	Screen screen;

	void reset();

	int stage = 0;
	int level = 0;
	int speed = 0;
	int score = 0;
	int highScore = 0;

	int getCurrentBG(){ return bgIndex; };
	void nextBG();
	void prevBG();
	void setBG(int i);

private:
	int bgCount;
	int bgIndex = 0;
};