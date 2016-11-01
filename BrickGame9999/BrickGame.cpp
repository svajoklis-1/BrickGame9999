#include "BrickGame.h"

#include "GSMenu.h"

#include "SaveManager.h"
#include "Global.h"

#include <iostream>

using namespace std;

BrickGame::BrickGame()
{
	res = new ResourceStore(scrRect);
	bgRenderer = new BackgroundRenderer(scrRect);
	scRenderer = new ScreenRenderer();
	soundPlayer = new SoundPlayer(res);

	device = new Device(soundPlayer);
	
	SaveManager::readSave(windowScale, framerateControl, *device);

	initSystem();

	configElements();
	configKeyMap();

	initDevice();

	// switch which gamestate is the startup one
#ifdef DEBUG_9999
	gameState = new GSMenu(*device);
	currentState = GS_MENU;
#else
	gameState = new GSMenu(device);
	currentState = GS_MENU;
#endif
}

void BrickGame::run()
{
	SDL_Event ev;

	int gameLoopStartTicks = 0;
	int gameLoopEndTicks = 0;

	while (!quitting)
	{
		gameLoopStartTicks = SDL_GetTicks();

		if (gameState->nextState != GS_NONE)
		{
			handleNextGameState(gameState->nextState);
		}

		while (SDL_PollEvent(&ev) != 0)
		{
			processEvent(ev);
		}

		if (!isMinimized)
		{
			// parse game keys

			if (!device->paused)
			{
				checkKeyboardState();

				gameState->postEvents(*device);
			}


			render(gameLoopStartTicks);
			deviceTick();

			gameLoopEndTicks = SDL_GetTicks();

		}

		updateWindowTitle(gameLoopStartTicks, gameLoopEndTicks);

		if (doReset)
		{
			doReset = false;
			gameState->nextState = GS_MENU;
			device->paused = false;
			device->screen.paused = false;
			device->reset();
		}
	}

	try
	{
		l.logPartial(Logger::INFO, "Attempting to save...");
		SaveManager::writeSave(windowScale, framerateControl, *device);
		l.logLabel(Logger::StatusLabel::OK);
	}
	catch (...)
	{
		l.logLabel(Logger::StatusLabel::FAIL);
		l.log(Logger::WARN, "Reverting to default save file");
		SaveManager::defaultSave(windowScale, framerateControl, *device);
		throw string("Writing save data failed, reverting to default...");
	}
	
}

void BrickGame::updateWindowTitle(int gameLoopStartTicks, int gameLoopEndTicks)
{
	// form window title
	char title[255];

	if (isMinimized)
	{
		sprintf_s(title, "BrickGame-9999");
	}
	else
	{
		if (gameLoopEndTicks - gameLoopStartTicks != 0)
		{
			sprintf_s(title, "BrickGame-9999 FPS:%d", int(1000.0 / (gameLoopEndTicks - gameLoopStartTicks)));
		}
		else
		{
			sprintf_s(title, "BrickGame-9999 FPS:1000+");
		}
	}

	SDL_SetWindowTitle(res->getWindow(), reinterpret_cast<char*>(&title));
}

void BrickGame::setWindowScale(int scale)
{
	SDL_SetWindowSize(res->getWindow(), res->windowSize.w * scale, res->windowSize.h * scale);
	SDL_RenderSetScale(r, static_cast<float>(scale), static_cast<float>(scale));
}