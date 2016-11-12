#pragma once

/* Screen that holds pixel arrays, various other screen elements */

#include "Types.hpp"
#include "ScreenNumber.hpp"
#include "PixelArray.hpp"

class Screen
{
public:
	Screen();
	~Screen();

	void clear();

	// number displays
	ScreenNumber score;
	ScreenNumber highScore;
	ScreenNumber level;
	ScreenNumber speed;

	// pixel arrays
	PixelArray mainArray;
	PixelArray hintArray;
};