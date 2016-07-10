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
	void increaseScore(int amount, char hiScoreLetter);
	map<char, int> highScore;
	map<char, int> getHighScores() const { return highScore; };

	int getCurrentBG() const { return bgIndex; };
	void nextBG();
	void prevBG();
	void setBG(int i);

	void setBGCount(int c){ bgCount = c; };
	int getBGCount() const { return bgCount; };

	int lives = 0;
	bool inGame = false;

	bool paused = false;
	bool pauseable = true;

private:
	int bgCount = 14;
	int bgIndex = 0;
};