#include "Screen.h"

Screen::Screen() :
score(6),
highScore(6),
level(1),
speed(1),
mainArray(10, 20),
hintArray(4, 4)
{
	clear();
}

Screen::PixelArray::PixelArray(int sizeX, int sizeY) :
sizeX(sizeX), sizeY(sizeY)
{
	pixels = new bool[sizeX * sizeY];
	clear();
}

Screen::PixelArray::~PixelArray()
{
	delete[] pixels;
}

Screen::~Screen()
{
	
}

void Screen::PixelArray::clear()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			setPixel(i, j, OFF);
		}
	}
}

void Screen::PixelArray::setPixel(int x, int y, pixelState state)
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
		return;
	
	pixels[xyToIndex(x, y)] = (bool)state;
}

int Screen::PixelArray::xyToIndex(int x, int y)
{
	return y * sizeX + x;
}

bool Screen::PixelArray::getPixel(int x, int y)
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
		return false;

	return pixels[xyToIndex(x, y)];
}

void Screen::clear()
{
	score.clear();
	highScore.clear();
	level.clear();
	speed.clear();

	mainArray.clear();
	hintArray.clear();
}