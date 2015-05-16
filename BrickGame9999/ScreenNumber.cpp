#include "ScreenNumber.h"

#include <SDL.h>

#include <cstdio>

ScreenNumber::ScreenNumber(int width, int initVal)
{
	this->width = width;

	segments = new int[width];

	for (int i = 0; i < width; i++)
	{
		segments[i] = NONE;
	}

	if (initVal >= 0)
		setNumber(initVal);
}

void ScreenNumber::clear()
{
	for (int i = 0; i < width; i++)
	{
		segments[i] = NONE;
	}
}

void ScreenNumber::dash()
{
	currentType = SEGMENTS;
	for (int i = 0; i < width; i++)
	{
		segments[i] = CENTER;
	}
}

void ScreenNumber::setNumber(int val)
{
	/*if (currentType == NUMBER && val == lastSetNumber)
		return;*/

	lastSetNumber = val;
	currentType = NUMBER;

	clear();

	bool sign;
	if (val >= 0)
		sign = false;
	else
		sign = true;
	int value = abs(val);
	int currentSegment = width - 1;

	while (value >= 0 && value < (1 * pow(10, width - (sign ? 1 : 0))))
	{
		switch (value % 10)
		{
		case 0:
			segments[currentSegment] = 
				TOP | UPPER_LEFT | UPPER_RIGHT | LOWER_LEFT | LOWER_RIGHT | BOTTOM;
			break;

		case 1:
			segments[currentSegment] =
				UPPER_RIGHT | LOWER_RIGHT;
			break;

		case 2:
			segments[currentSegment] =
				TOP | UPPER_RIGHT | CENTER | LOWER_LEFT | BOTTOM;
			break;

		case 3:
			segments[currentSegment] =
				TOP | UPPER_RIGHT | CENTER | LOWER_RIGHT | BOTTOM;
			break;

		case 4:
			segments[currentSegment] =
				UPPER_LEFT | CENTER | UPPER_RIGHT | LOWER_RIGHT;
			break;

		case 5:
			segments[currentSegment] =
				TOP | UPPER_LEFT | CENTER | LOWER_RIGHT | BOTTOM;
			break;

		case 6:
			segments[currentSegment] =
				TOP | UPPER_LEFT | CENTER | LOWER_LEFT | BOTTOM | LOWER_RIGHT;
			break;

		case 7:
			segments[currentSegment] =
				TOP | UPPER_RIGHT | LOWER_RIGHT;
			break;

		case 8:
			segments[currentSegment] =
				TOP | UPPER_LEFT | UPPER_RIGHT | CENTER | LOWER_LEFT | LOWER_RIGHT | BOTTOM;
			break;

		case 9:
			segments[currentSegment] =
				TOP | UPPER_LEFT | UPPER_RIGHT | CENTER | LOWER_RIGHT | BOTTOM;
			break;

		}

		currentSegment--;

		value = value / 10;
		if (value == 0)
			value = -1;
	}

	if (sign && value < (1 * pow(10, width - 1)))
		segments[currentSegment] = CENTER;
}

void ScreenNumber::render(ResourceStore &res, coord where)
{
	SDL_Rect from = { 0, 0, res.item["digit"].w, res.item["digit"].h };
	SDL_Rect to = { where.x, where.y, res.item["digit"].w, res.item["digit"].h };

	SDL_Texture *segmentTex = res.img("segments.png");

	for (int i = width - 1; i >= 0; i--)
	{
		if ((segments[i] & TOP) > 0)
		{
			from.x = 0 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & UPPER_RIGHT) > 0)
		{
			from.x = 1 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & UPPER_LEFT) > 0)
		{
			from.x = 2 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & CENTER) > 0)
		{
			from.x = 3 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & LOWER_RIGHT) > 0)
		{
			from.x = 4 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & LOWER_LEFT) > 0)
		{
			from.x = 5 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segments[i] & BOTTOM) > 0)
		{
			from.x = 6 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		to.x = to.x - res.item["digit"].w - 1;
	}
}

ScreenNumber::~ScreenNumber()
{
	delete[] segments;
}

void ScreenNumber::setSegments(int *segments, int segmentCount)
{
	for (int i = 0; (i < segmentCount) && (i < width); i++)
	{
		this->segments[i] = segments[i];
	}
}