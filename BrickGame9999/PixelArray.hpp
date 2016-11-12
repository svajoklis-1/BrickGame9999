#pragma once

#include "Types.hpp"

#include <string>

using namespace std;

const bool PXARRAY_ON = true;
const bool PXARRAY_OFF = false;

class PixelArray
{
public:
	PixelArray(int sizeX, int sizeY);
	~PixelArray();

	void setPixel(int x, int y, bool state);
	void setPixel(coord c, bool state) { setPixel(c.x, c.y, state); };
	bool getPixel(int x, int y);
	bool getPixel(coord c) { return getPixel(c.x, c.y); }

	int cToIndex(coord c) { return xyToIndex(c.x, c.y); }
	int xyToIndex(int x, int y);
	void clear();

	int getSizeX() { return sizeX; };
	int getSizeY() { return sizeY; };

	void fillLines(int from, int to);
	void setCount(int c);

	void copyArray(int x, int y, bool *data, int w, int h);
	void copyString(int x, int y, string data, int w, int h, bool withWhitespace = false);

private:
	int sizeX, sizeY;
	bool *pixels;
};