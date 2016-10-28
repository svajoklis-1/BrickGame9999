#include "BrickGame.h"

void BrickGame::render(int gameLoopStartTicks)
{
	// render background
	bgRenderer->render(*res, device->getCurrentBG());

	scRenderer->render(device->screen, *res);

	SDL_RenderPresent(res->getRenderer());

	// framerate limit
	int ticksNow = SDL_GetTicks();

	int fps = 250;
	if ((ticksNow - gameLoopStartTicks) < (1000 / fps) && (framerateControl == FRC_250))
	{
		SDL_Delay((1000 / fps) - (ticksNow - gameLoopStartTicks));
		ticksNow = SDL_GetTicks();
	}
}