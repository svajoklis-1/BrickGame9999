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

	int getLevel() { return level; };
	int getSpeed() { return speed; };
	int &getLevelRef() { return this->level; };
	int &getSpeedRef() { return this->speed; };
	void setLevel(int level);
	void setSpeed(int speed);
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
	int level = 0;
	int speed = 0;

	int bgCount = 1;
	int bgIndex = 0;
};