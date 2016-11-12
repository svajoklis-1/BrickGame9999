#pragma once

/* SDL dependent screen renderer that is able to render a device Screen to screen */

#include "Screen.hpp"
#include "ResourceStore.hpp"
#include "PixelArray.hpp"
#include "Device.hpp"
#include "PixelArrayRenderer.hpp"
#include "ScreenNumber.hpp"

class ScreenRenderer
{
public:
	ScreenRenderer();
	~ScreenRenderer();
	void render(Device &dev, ResourceStore &res);
	void preDeviceRender();
	void postDeviceRender();

private:
	void renderItem(ResourceStore &res, string item);
	void renderScreenNumber(ResourceStore &res, ScreenNumber &number, string locationId);

	PixelArrayRenderer mainScreen;
	PixelArrayRenderer hintScreen;
};