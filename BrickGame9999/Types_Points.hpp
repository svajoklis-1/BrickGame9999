#pragma once

#include "Types.hpp"

class point
{
public:
	int x;
	int y;

	point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	point()
	{
		this->x = 0;
		this->y = 0;
	}

	bool operator ==(const point &other) const
	{
		if (x == other.x && y == other.y)
		{
			return true;
		}

		return false;
	}

	point &setX(int x)
	{
		this->x = x;
		return *this;
	}

	point &setY(int y)
	{
		this->y = y;
		return *this;
	}

	point &addX(int x)
	{
		this->x += x;
		return *this;
	}

	point &addY(int y)
	{
		this->y += y;
		return *this;
	}
};

class rect : public point
{
public:
	int w;
	int h;

	rect(int x, int y, int w, int h) : point(x, y)
	{
		this->w = w;
		this->h = h;
	}

	bool operator ==(const rect &other) const
	{
		if (point::operator==(other) && w == other.w && h == other.h)
		{
			return true;
		}

		return false;
	}

	rect &setW(int w)
	{
		this->w = w;
		return *this;
	}

	rect &setH(int h)
	{
		this->h = h;
		return *this;
	}

	rect &addW(int w)
	{
		this->w += w;
		return *this;
	}

	rect &addH(int h)
	{
		this->h += h;
		return *this;
	}
};

class moving_point : public point
{
public:
	int dx;
	int dy;

	moving_point(int x, int y, int dx, int dy) : point(x, y)
	{
		this->dx = dx;
		this->dy = dy;
	}

	bool operator ==(const moving_point &other) const
	{
		if (point::operator==(other) && dx == other.dx && dy == other.dy)
		{
			return true;
		}

		return false;
	}

	moving_point &setDX(int dx)
	{
		this->dx = dx;
		return *this;
	}

	moving_point &setDY(int dy)
	{
		this->dy = dy;
		return *this;
	}

	moving_point &moveByDelta()
	{
		this->x += this->dx;
		this->y += this->dy;

		return *this;
	}

	moving_point &addDX(int dx)
	{
		this->dx += dx;
		return *this;
	}

	moving_point &addDY(int dy)
	{
		this->dy += dy;
		return *this;
	}

	point toPoint()
	{
		return point(this->x, this->y);
	}
};