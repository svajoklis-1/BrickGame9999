#pragma once

#include "ResourceStore.h"

enum segment
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

class ScreenNumber
{
public:
	ScreenNumber(int width, int initVal = -1);
	~ScreenNumber();

	void clear();
	void dash();

	void setNumber(int value);
	void setSegments(int *segments, int segmentCount);

	void setLink(int *value){ this->link = value; };
	void setLinked() { if (link) setNumber(*link); else setNumber(0); }

	void render(ResourceStore &res, coord where);
private:
	int *link = nullptr;

	int width = 0;
	int *segments;
};