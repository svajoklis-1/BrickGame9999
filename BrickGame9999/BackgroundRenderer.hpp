#pragma once

#include "ResourceStore.hpp"

class BackgroundRenderer
{
public:
	BackgroundRenderer(SDL_Rect windowSize);

	void render(ResourceStore &res);
	void setBackground(int i);

private:
	int currentBGIndex = 0;

	SDL_Rect currentBG;
	SDL_Rect screenRect;
};