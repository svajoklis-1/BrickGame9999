#pragma once

#include "ResourceStore.hpp"



class ScreenNumber
{
public:
	enum Segment
	{
		NONE = 0,
		TOP = 1,
		UPPER_RIGHT = 2,
		UPPER_LEFT = 4,
		CENTER = 8,
		LOWER_RIGHT = 16,
		LOWER_LEFT = 32,
		BOTTOM = 64
	};

	ScreenNumber(int width, int initVal = -1);
	~ScreenNumber();

	void clear();
	void dash();

	void setNumber(int value);
	void setSegments(int *segments, int segmentCount);

	void setLink(int *value);
	void setLinked();

	int getSegment(int index);
	int getSegmentCount();
private:
	int *link = nullptr;

	enum types
	{
		NUMBER,
		SEGMENTS,
		LINK
	};

	int lastSetNumber = 0;
	int currentType = SEGMENTS;

	int width = 0;
	int *segments;
};