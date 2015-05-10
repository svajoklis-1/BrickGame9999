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

void Screen::PixelArray::fillLines(int from, int to)
{
	if (to <= from)
		return;
	if (from < 0 || to > sizeY)
		return;

	for (int i = from; i < to; i++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			pixels[i*sizeX + x] = ON;
		}
	}
}

void Screen::PixelArray::setCount(int c)
{
	clear();

	if (c < 0)
		return;

	if (c > sizeX * sizeY)
		c = sizeX * sizeY;

	int curX = 0, curY = 0;
	while (c > 0)
	{
		setPixel(curX, curY, ON);
		curX++;
		if (curX == sizeX)
		{
			curX = 0; curY++;
		}

		c--;
	}
}

void Screen::PixelArray::copyArray(int x, int y, bool* data, int w, int h)
{
	for (int i = x; i < x + w && i < sizeX; i++)
	{
		for (int j = y; j < x + h && j < sizeY; j++)
		{
			pixels[j * sizeX + i] = data[(j - y) * w + (i - x)];
		}
	}
}

void Screen::PixelArray::copyString(int x, int y, string data, int w, int h)
{
	for (int i = x; i < x + w && i < sizeX; i++)
	{
		for (int j = y; j < y + h && j < sizeY; j++)
		{
			pixels[j * sizeX + i] = data[(j - y) * w + (i - x)] != ' ';
		}
	}
}
