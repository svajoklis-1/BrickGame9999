#include "BrickGame.hpp"

void BrickGame::configElements()
{
	res->location["screen"] = { 46, 18 };
	res->location["hint"] = { 149, 81 };
	res->location["score"] = { 181, 28 };
	res->location["hiscore"] = { 181, 58 };

	res->location["level"] = { 161, 149 };
	res->location["speed"] = { 161, 131 };

	res->location["note"] = { 147, 181 };
	res->location["cup"] = { 167, 182 };

	res->item["screenPixel"] = { 1, 1, 8, 8 };
	res->item["hintPixel"] = { 10, 1, 7, 7 };
	res->item["note"] = { 18, 1, 11, 14 };
	res->item["cup"] = { 31, 1, 15, 12 };
	res->item["screenPixelShadow"] = { 1, 10, 8, 8 };

	res->item["digit"] = { 0, 0, 7, 15 };
}

void BrickGame::configKeyMap()
{
	keyMap[KEY_UP] = SDL_SCANCODE_UP;
	keyMap[KEY_DOWN] = SDL_SCANCODE_DOWN;
	keyMap[KEY_LEFT] = SDL_SCANCODE_LEFT;
	keyMap[KEY_RIGHT] = SDL_SCANCODE_RIGHT;
	keyMap[KEY_ACTION] = SDL_SCANCODE_SPACE;

	keyMap[KEY_START] = SDL_SCANCODE_RETURN;
	keyMap[KEY_RESET] = SDL_SCANCODE_F1;
}