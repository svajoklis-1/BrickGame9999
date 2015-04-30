#include "BackgroundRenderer.h"

BackgroundRenderer::BackgroundRenderer(SDL_Rect windowSize)
{
	currentBG = { 0, 0, windowSize.w, windowSize.h };
	screenRect = { 0, 0, windowSize.w, windowSize.h };
}

void BackgroundRenderer::render(ResourceStore &res, int bgIndex)
{ 
	setBackground(bgIndex);

	SDL_RenderCopy(res.getRenderer(), res.img("bgs.png"), &currentBG, &screenRect);
	SDL_RenderCopy(res.getRenderer(), res.img("screen.png"), &screenRect, &screenRect);
}

void BackgroundRenderer::setBackground(int i)
{
	if (i == currentBGIndex)
		return;

	int column = i % 4;
	int row = i / 4;

	currentBG = { column * screenRect.w, row * screenRect.h, screenRect.w, screenRect.h };
	currentBGIndex = i;
}