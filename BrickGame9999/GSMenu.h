#pragma once

#include "GameState.h"
#include "Ticker.h"

#include <string>
using namespace std;

using namespace std;

class GSMenu : public GameState
{
public:
	GSMenu(Device &dev);
	~GSMenu();
	void tick(Device &dev) override;
	void parseEvent(Device &dev, Key k) override;
	void render(Device &dev) override;

private:

	enum letters
	{
		A = 0,
		B,
		C,
		D,
		E,
		G,
		R,
		S,
		LETTER_COUNT
	};

	void defineGraphics();

	// numbers
	string numbers[10];
	int numCount = 10;

	map<int, string[4]> anims;

	const int numberH = 5;
	const int numberW = 3;
	const int numberX = 1;
	const int numberY = 15;

	static int currentL;

	void drawNumber(Device &dev);

	// letter related stuffs
	string letters[LETTER_COUNT];

	const int letterX = 2;
	const int letterY = 0;
	const int letterCount = LETTER_COUNT;
	const int letterW = 5;
	const int letterH = 5;

	void drawLetter(Device &dev);
	void renderAnim(Device &dev);

	int flipTick = 0;
	int flipState = 1;
	int flipDir = 1;
	const int turnDelay = 60; //was60
	int turnDelayTick = 0;
	bool turning = false;

	Ticker animTicker;
	int animFrame = 0;
	int animW = 8, animH = 8;
};