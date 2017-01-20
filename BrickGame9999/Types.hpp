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

enum Direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

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
#define key_depressed(a) a == STATE_UP

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