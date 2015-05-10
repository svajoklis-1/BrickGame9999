#pragma once

#include "Screen.h"

#include <map>
using namespace std;

class Device
{
public:
	Device() {};
	Screen screen;

	void reset();
	
	// from main menu
	int stage = 0;

	int level = 0;
	int speed = 0;
	int score = 0;
	map<char, int> highScore;

	int getCurrentBG(){ return bgIndex; };
	void nextBG();
	void prevBG();
	void setBG(int i);

	void setBGCount(int c){ bgCount = c; };
	int getBGCount(){ return bgCount; }

	int lives = 0;
	bool inGame = false;

private:
	int bgCount = 14;
	int bgIndex = 0;
};