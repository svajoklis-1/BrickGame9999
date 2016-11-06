#include "ScreenRenderer.h"

#include <cmath>

#include "Global.h"

ScreenRenderer::ScreenRenderer() :
mainScreen(10, 20, 4),
hintScreen(4, 4, 4)
{
}

ScreenRenderer::~ScreenRenderer()
{
}

void ScreenRenderer::render(Device &dev, ResourceStore &res)
{
	mainScreen.render(dev.screen.mainArray, res, "screen", "screenPixel");
	hintScreen.render(dev.screen.hintArray, res, "hint", "hintPixel");

	// render numbers

	renderScreenNumber(res, dev.screen.score, "score");
	renderScreenNumber(res, dev.screen.highScore, "hiscore");
	renderScreenNumber(res, dev.screen.level, "level");
	renderScreenNumber(res, dev.screen.speed, "speed");

	// render icons

	if (!dev.speaker.isMuted())
	{
		renderItem(res, "note");
	}

	if (dev.paused)
	{
		renderItem(res, "cup");
	}

}

void ScreenRenderer::renderItem(ResourceStore &res, string item)
{
	SDL_Rect dest;
	dest.x = res.location[item].x;
	dest.y = res.location[item].y;
	dest.w = res.item[item].w;
	dest.h = res.item[item].h;
	SDL_RenderCopy(
		res.getRenderer(),
		res.img("items.png"),
		&res.item[item],
		&dest);
}

void ScreenRenderer::preDeviceRender()
{

}

void ScreenRenderer::postDeviceRender()
{
	mainScreen.pushPrevs();
	hintScreen.pushPrevs();
}

void ScreenRenderer::renderScreenNumber(ResourceStore &res, ScreenNumber &number, string locationId)
{
	SDL_Rect from = { 0, 0, res.item["digit"].w, res.item["digit"].h };
	coord location = res.location[locationId];
	SDL_Rect to = { location.x, location.y, res.item["digit"].w, res.item["digit"].h };

	SDL_Texture *segmentTex = res.img("segments.png");

	for (int i = number.getSegmentCount() - 1; i >= 0; i--)
	{
		int segment = number.getSegment(i);
		if ((segment & ScreenNumber::TOP) > 0)
		{
			from.x = 0 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::UPPER_RIGHT) > 0)
		{
			from.x = 1 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::UPPER_LEFT) > 0)
		{
			from.x = 2 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::CENTER) > 0)
		{
			from.x = 3 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::LOWER_RIGHT) > 0)
		{
			from.x = 4 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::LOWER_LEFT) > 0)
		{
			from.x = 5 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		if ((segment & ScreenNumber::BOTTOM) > 0)
		{
			from.x = 6 * res.item["digit"].w;

			SDL_RenderCopy(
				res.getRenderer(),
				segmentTex,
				&from,
				&to);
		}

		to.x = to.x - res.item["digit"].w - 1;
	}
}