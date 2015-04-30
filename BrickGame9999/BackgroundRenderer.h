#pragma once

#include "ResourceStore.h"

class BackgroundRenderer
{
public:
	BackgroundRenderer(SDL_Rect windowSize);

	void render(ResourceStore &res, int bgIndex);
	

private:
	int currentBGIndex = 0;

	void setBackground(int i);

	SDL_Rect currentBG;
	SDL_Rect screenRect;
};