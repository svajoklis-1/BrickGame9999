#include "BackgroundRenderer.hpp"
#include "Global.hpp"

BackgroundRenderer::BackgroundRenderer(SDL_Rect windowSize)
{
	currentBG = { 0, 0, windowSize.w, windowSize.h };
	screenRect = { 0, 0, windowSize.w, windowSize.h };
}

void BackgroundRenderer::render(ResourceStore &res)
{ 
	SDL_RenderCopy(res.getRenderer(), res.img("bgs.png"), &currentBG, &screenRect);
	SDL_RenderCopy(res.getRenderer(), res.img("screen.png"), &screenRect, &screenRect);
}

void BackgroundRenderer::setBackground(int i)
{
	if (i == currentBGIndex)
	{
		l.log(Logger::WARN, "Switching to the background that is currently selected");
		return;
	}

	int column = i % 4;
	int row = i / 4;

	currentBG = { column * screenRect.w, row * screenRect.h, screenRect.w, screenRect.h };
	currentBGIndex = i;
}