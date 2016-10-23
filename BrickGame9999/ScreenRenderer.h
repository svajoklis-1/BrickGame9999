#pragma once

/* SDL dependent screen renderer that is able to render a device Screen to screen */

#include "Screen.h"
#include "ResourceStore.h"



class ScreenRenderer
{
public:
	ScreenRenderer();
	~ScreenRenderer();
	void render(Screen &screen, ResourceStore &res);
	void preRender();
	void postRender();

	class ScreenRenderHelper
	{
	public:
		ScreenRenderHelper(int sizeX, int sizeY, int numShadows);
		~ScreenRenderHelper();

		void render(Screen::PixelArray &array, ResourceStore &res, string location, string item);

		int sizeX, sizeY;

		int numShadows;
		bool **prevScreen;
		bool *renderedScreen;

		void pushPrevs();

	private:
		void renderArray(bool *data, int sizeX, int sizeY, ResourceStore &res, string location, string item, bool *renderMask, int opacity = 255);
	};

private:
	void renderNum(Screen &screen, ResourceStore &res, int num, coord where, int width);
	void renderItem(ResourceStore &res, string item);

	ScreenRenderHelper mainScreen;
	ScreenRenderHelper hintScreen;
};