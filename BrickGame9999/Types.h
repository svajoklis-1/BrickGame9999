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

enum Key
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ACTION
};

enum GameStates
{
	GS_NONE,
	GS_MENU,
	GS_RAIN,
	GS_SNAKE,
	GS_GAMEOVER,
	GS_GAMEOVER_TOCURRENT
};