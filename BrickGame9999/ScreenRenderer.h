#pragma once

/* SDL dependent screen renderer that is able to render a device Screen to screen */

#include "Screen.h"
#include "ResourceStore.h"
#include "PixelArray.h"
#include "Device.h"
#include "PixelArrayRenderer.h"
#include "ScreenNumber.h"

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