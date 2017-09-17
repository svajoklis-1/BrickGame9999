#include "Explosion.hpp"

Explosion::Explosion() :
	displayTicker(5)
{
	explosionPosition = { 0, 0 };

	frames[0] =
		"*  *"
		" ** "
		" ** "
		"*  *";

	frames[1] =
		" ** "
		"*  *"
		"*  *"
		" ** ";

	currentFrame = 0;
}

void Explosion::render(Device& dev)
{
	if (displayTicker.triggered())
	{
		displayTicker.reset();
		currentFrame++; if (currentFrame == 2) currentFrame = 0;
	}
	else
	{
		displayTicker.tick();
	}

	dev.screen.mainArray.copyString(explosionPosition.x, explosionPosition.y, frames[currentFrame], 4, 4, true);
}
