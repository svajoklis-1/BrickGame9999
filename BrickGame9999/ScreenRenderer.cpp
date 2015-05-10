#include "ScreenRenderer.h"

#include <cmath>

ScreenRenderer::ScreenRenderer() :
mainScreen(10, 20, 4),
hintScreen(4, 4, 4)
{
}

ScreenRenderer::~ScreenRenderer()
{
}

void ScreenRenderer::render(Screen &screen, ResourceStore &res)
{
	mainScreen.render(screen.mainArray, res, "screen", "screenPixel");
	hintScreen.render(screen.hintArray, res, "hint", "hintPixel");

	// render numbers

	screen.score.render(res, res.location["score"]);
	screen.highScore.render(res, res.location["hiscore"]);
	screen.level.render(res, res.location["level"]);
	screen.speed.render(res, res.location["speed"]);
}

void ScreenRenderer::moveShadows()
{
	mainScreen.moveShadows();
	hintScreen.moveShadows();
}

void ScreenRenderer::renderNum(Screen &screen, ResourceStore &res, int num, coord where, int width)
{
	int score = num;
	int x = where.x;
	int y = where.y;

	while (score >= 0 && score < (1 * pow(10, width)))
	{
		SDL_Rect src;
		src.x = (score % 10) * res.item["digit"].w;
		src.y = 0;
		src.w = res.item["digit"].w;
		src.h = res.item["digit"].h;

		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = src.w;
		dest.h = src.h;

		SDL_RenderCopy(
			res.getRenderer(),
			res.img("digits.png"),
			&src,
			&dest);

		x = x - (res.item["digit"].w + 1);

		score = score / 10;

		if (score == 0)
			score = -1;
	}
}

// --------------------------------- SCREEN RENDER HELPER ---------------------------------------------------------------

void ScreenRenderer::ScreenRenderHelper::renderArray(bool *data, int sizeX, int sizeY, ResourceStore &res, string location, string item, bool *renderMask, int opacity)
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			bool pixelVal = data[y * sizeX + x];

			if (!pixelVal || renderedScreen[y * sizeX + x])
				continue;

			renderedScreen[y * sizeX + x] = true;

			SDL_Rect pixel;
			pixel.x = res.location[location].x + (x * (res.item[item].w + 1));
			pixel.y = res.location[location].y + (y * (res.item[item].h + 1));
			pixel.w = res.item[item].w;
			pixel.h = res.item[item].h;

			SDL_SetTextureAlphaMod(res.img("items.png"), opacity);

			SDL_RenderCopy(
				res.getRenderer(),
				res.img("items.png"),
				&res.item[item],
				&pixel);

			SDL_SetTextureAlphaMod(res.img("items.png"), 255);
		}
	}
}

ScreenRenderer::ScreenRenderHelper::ScreenRenderHelper(int sizeX, int sizeY, int numShadows) :
sizeX(sizeX), sizeY(sizeY), numShadows(numShadows)
{
	prevScreen = new bool*[numShadows];

	for (int i = 0; i < numShadows; i++)
	{
		prevScreen[i] = new bool[sizeX * sizeY];

		for (int x = 0; x < sizeX * sizeY; x++)
		{
			prevScreen[i][x] = false;
		}
	}

	renderedScreen = new bool[sizeX * sizeY];
}

ScreenRenderer::ScreenRenderHelper::~ScreenRenderHelper()
{
	for (int i = 0; i < numShadows; i++)
	{
		delete[] (prevScreen[i]);
	}

	delete[] prevScreen;

	delete[] renderedScreen;
}

void ScreenRenderer::ScreenRenderHelper::render(Screen::PixelArray &array, ResourceStore &res, string location, string item)
{
	// render shadows 

	for (int i = 0; i < sizeX * sizeY; i++)
		renderedScreen[i] = false;

	int alpha = 255;
	for (int i = 0; i < numShadows; i++)
	{
		alpha -= 255 / (numShadows + 1);
		renderArray(prevScreen[i], sizeX, sizeY, res, location, item, renderedScreen, alpha);
	}

	// was move shadows

	// render main pixel array

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			bool pixelVal = array.getPixel(x, y);

			if(numShadows > 0) prevScreen[0][y * sizeX + x] = pixelVal;
			if (!pixelVal)
				continue;

			SDL_Rect pixel;
			pixel.x = res.location[location].x + (x * (res.item[item].w + 1));
			pixel.y = res.location[location].y + (y * (res.item[item].h + 1));
			pixel.w = res.item[item].w;
			pixel.h = res.item[item].h;

			SDL_RenderCopy(
				res.getRenderer(),
				res.img("items.png"),
				&res.item[item],
				&pixel);
		}
	}
}

void ScreenRenderer::ScreenRenderHelper::pushPrevs()
{
	for (int i = numShadows - 2; i >= 0; i--)
	{
		for (int n = 0; n < sizeX * sizeY; n++)
		{
			prevScreen[i + 1][n] = prevScreen[i][n];
		}
	}
}

void ScreenRenderer::ScreenRenderHelper::moveShadows()
{
	pushPrevs();
}