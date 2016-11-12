#include "BrickGame.hpp"

void BrickGame::deviceTick()
{
	// if tick is ok or framerate is vsynced
	if ((SDL_GetTicks() - lastDeviceTick) > (1000.f / static_cast<float>(deviceTickLength)) || (framerateControl == FRC_VSYNC))
	{
		lastDeviceTick = SDL_GetTicks();
		if (!device->paused)
			gameState->tick(*device);

		scRenderer->preDeviceRender();

		// let the game render on the device
		gameState->render(*device);

		scRenderer->postDeviceRender();
	}
}