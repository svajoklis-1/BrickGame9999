#include "ScreenNumber.hpp"

#include <SDL.h>

#include "Global.hpp"

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

int ScreenNumber::getSegment(int index) {

	if (index < 0 || index >= width)
	{
		l.log(Logger::ASSERT, "Attempting to access screen number segment (%d), beyond array length (%d)", index, width);
		return Segment::NONE;
	}

	return segments[index];
}

int ScreenNumber::getSegmentCount()
{
	return width;
}

void ScreenNumber::setLink(int *value)
{ 
	this->link = value;
}

void ScreenNumber::setLinked()
{
	if (link)
	{
		setNumber(*link);
	}
	else
	{
		setNumber(0);
	}
}