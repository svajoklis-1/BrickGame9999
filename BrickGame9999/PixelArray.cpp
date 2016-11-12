#include "PixelArray.hpp"
#include "Types.hpp"


PixelArray::PixelArray(int sizeX, int sizeY) :
	sizeX(sizeX), sizeY(sizeY)
{
	pixels = new bool[sizeX * sizeY];
	clear();
}

PixelArray::~PixelArray()
{
	delete[] pixels;
}


void PixelArray::clear()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			setPixel(i, j, PXARRAY_OFF);
		}
	}
}

void PixelArray::setPixel(int x, int y, bool state)
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
		return;

	pixels[xyToIndex(x, y)] = state;
}

int PixelArray::xyToIndex(int x, int y)
{
	return y * sizeX + x;
}

bool PixelArray::getPixel(int x, int y)
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
		return false;

	return pixels[xyToIndex(x, y)];
}



void PixelArray::fillLines(int from, int to)
{
	if (to <= from)
		return;
	if (from < 0 || to > sizeY)
		return;

	for (int i = from; i < to; i++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			pixels[i*sizeX + x] = PXARRAY_ON;
		}
	}
}

void PixelArray::setCount(int c)
{
	clear();

	if (c < 0)
		return;

	if (c > sizeX * sizeY)
		c = sizeX * sizeY;

	int curX = 0, curY = 0;
	while (c > 0)
	{
		setPixel(curX, curY, PXARRAY_ON);
		curX++;
		if (curX == sizeX)
		{
			curX = 0; curY++;
		}

		c--;
	}
}

void PixelArray::copyArray(int x, int y, bool* data, int w, int h)
{
	for (int i = (x >= 0 ? x : 0); i < x + w && i < sizeX; i++)
	{
		for (int j = (y >= 0 ? y : 0); j < x + h && j < sizeY; j++)
		{
			pixels[j * sizeX + i] = data[(j - y) * w + (i - x)];
		}
	}
}

void PixelArray::copyString(int x, int y, string data, int w, int h, bool withWhitespace)
{
	for (int i = (x >= 0 ? x : 0); (i < x + w) && (i < sizeX); i++)
	{
		for (int j = (y >= 0 ? y : 0); (j < y + h) && (j < sizeY); j++)
		{
			if (data[(j - y) * w + (i - x)] != ' ')
				pixels[j * sizeX + i] = PXARRAY_ON;

			if (withWhitespace && data[(j - y) * w + (i - x)] == ' ')
				pixels[j * sizeX + i] = PXARRAY_OFF;
		}
	}
}
