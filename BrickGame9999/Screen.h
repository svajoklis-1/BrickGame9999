#pragma once

#include "Types.h"
#include "ScreenNumber.h"

enum pixelState
{
	ON = true,
	OFF = false
};

class Screen
{
public:
	Screen();
	~Screen();

	void clear();

	class PixelArray
	{
	public:
		PixelArray(int sizeX, int sizeY);
		~PixelArray();

		void setPixel(int x, int y, pixelState state);
		void setPixel(coord c, pixelState state) { setPixel(c.x, c.y, state); };
		bool getPixel(int x, int y);
		bool getPixel(coord c){ return getPixel(c.x, c.y); }

		int cToIndex(coord c){ return xyToIndex(c.x, c.y); }
		int xyToIndex(int x, int y);
		void clear();

		int getSizeX(){ return sizeX; };
		int getSizeY(){ return sizeY; };

		void fillLines(int from, int to);
		void setCount(int c);
	private:
		int sizeX, sizeY;
		bool *pixels;
	};

	bool music = false;

	ScreenNumber score;
	ScreenNumber highScore;
	ScreenNumber level;
	ScreenNumber speed;

	PixelArray mainArray;
	PixelArray hintArray;

private:
};