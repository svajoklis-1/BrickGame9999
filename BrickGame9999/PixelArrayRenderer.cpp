#include "PixelArrayRenderer.hpp"

void PixelArrayRenderer::renderArray(bool *data, int dataSizeX, int dataSizeY, ResourceStore &res, string location, string item, bool * /*renderMask*/, int opacity)
{
	for (int x = 0; x < dataSizeX; x++)
	{
		for (int y = 0; y < dataSizeY; y++)
		{
			bool pixelVal = data[y * dataSizeX + x];

			if (!pixelVal || renderedScreen[y * dataSizeX + x])
				continue;

			renderedScreen[y * dataSizeX + x] = true;

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

PixelArrayRenderer::PixelArrayRenderer(int sizeX, int sizeY, int numShadows) :
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

PixelArrayRenderer::~PixelArrayRenderer()
{
	for (int i = 0; i < numShadows; i++)
	{
		delete[](prevScreen[i]);
	}

	delete[] prevScreen;

	delete[] renderedScreen;
}

void PixelArrayRenderer::render(PixelArray &array, ResourceStore &res, string location, string item)
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

			if (numShadows > 0) prevScreen[0][y * sizeX + x] = pixelVal;
			if (!pixelVal)
			{
				continue;
			}
				
			SDL_Rect pixel;
			pixel.x = res.location[location].x + (x * (res.item[item].w + 1));
			pixel.y = res.location[location].y + (y * (res.item[item].h + 1));
			pixel.w = res.item[item].w;
			pixel.h = res.item[item].h;

			SDL_RenderCopy(
				res.getRenderer(),
				res.img("items.png"),
				&res.item[item],
				&pixel
			);
		}
	}
}

void PixelArrayRenderer::pushPrevs()
{
	for (
		int secondToLast = numShadows - 2, last = numShadows - 1;
		secondToLast >= 0 && last >= 1;
		secondToLast--, last--
	)
	{
		for (int n = 0; n < sizeX * sizeY; n++)
		{
			prevScreen[last][n] = prevScreen[secondToLast][n];
		}
	}
}