#pragma once

#include "Types.h"
#include "ScreenNumber.h"

const bool ON = true;
const bool OFF = false;

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

		void setPixel(int x, int y, bool state);
		void setPixel(coord c, bool state) { setPixel(c.x, c.y, state); };
		bool getPixel(int x, int y);
		bool getPixel(coord c){ return getPixel(c.x, c.y); }

		int cToIndex(coord c){ return xyToIndex(c.x, c.y); }
		int xyToIndex(int x, int y);
		void clear();

		int getSizeX(){ return sizeX; };
		int getSizeY(){ return sizeY; };

		void fillLines(int from, int to);
		void setCount(int c);

		void copyArray(int x, int y, bool *data, int w, int h);
		void copyString(int x, int y, string data, int w, int h, bool withWhitespace = false);

	private:
		int sizeX, sizeY;
		bool *pixels;
	};

	bool sound = false;
	bool paused = false;

	ScreenNumber score;
	ScreenNumber highScore;
	ScreenNumber level;
	ScreenNumber speed;

	PixelArray mainArray;
	PixelArray hintArray;
};