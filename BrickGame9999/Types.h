#pragma once

struct coord
{
	int x;
	int y;

	bool operator ==(const coord &other) const
	{
		if (x == other.x && y == other.y)
			return true;

		return false;
	}
};