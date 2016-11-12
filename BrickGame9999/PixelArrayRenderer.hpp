#pragma once

#include "PixelArray.hpp"
#include "ResourceStore.hpp"
#include <string>
using namespace std;

class PixelArrayRenderer
{
public:
	PixelArrayRenderer(int sizeX, int sizeY, int numShadows);
	~PixelArrayRenderer();

	void render(PixelArray &array, ResourceStore &res, string location, string item);

	int sizeX, sizeY;

	int numShadows;
	bool **prevScreen;
	bool *renderedScreen;

	void pushPrevs();

private:
	void renderArray(bool *data, int sizeX, int sizeY, ResourceStore &res, string location, string item, bool *renderMask, int opacity = 255);
};