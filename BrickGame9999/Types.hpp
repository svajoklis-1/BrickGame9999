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

class point;
class moving_point;
class rect;

enum Direction
{
	DIR_UP = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 4,
	DIR_RIGHT = 8
};

inline int dxOfDirection(Direction dir)
{
	if((dir & DIR_LEFT) > 0)
	{
		return -1;
	}

	if((dir & DIR_RIGHT) > 0)
	{
		return 1;
	}

	return 0;
}

inline int dyOfDirection(Direction dir)
{
	if ((dir & DIR_UP) > 0)
	{
		return -1;
	}

	if ((dir & DIR_DOWN) > 0)
	{
		return 1;
	}

	return 0;
}

#include "Types_Points.hpp"

enum Key
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ACTION,

	KEY_START,
	KEY_RESET,
	KEY_TOTAL
};

enum Sound
{
	SND_BLIP,
	SND_BOUNCE,
	SND_EXPLODE
};

enum KeyState
{
	STATE_UP,
	STATE_DOWN,
	STATE_HELD
};

#define key_held(a) a == STATE_DOWN || a == STATE_HELD
#define key_pressed(a) a == STATE_DOWN
#define key_released(a) a == STATE_UP

enum GameStates
{
	GS_NONE,
	GS_MENU,
	GS_RAIN,
	GS_SNAKE,
	GS_SNAKEINF,
	GS_ARKANOID,
	GS_DEFEND,
	GS_GAMEOVER,
	GS_GAMEOVER_TOCURRENT
};