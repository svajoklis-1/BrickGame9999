#include "BrickGame.hpp"

#include "GSMenu.hpp"

#include "SaveManager.hpp"
#include "Global.hpp"

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

	bgRenderer->setBackground(device->getCurrentBG());

	initSystem();

	configElements();
	configKeyMap();

	initDevice();

	this->fpsHistory = new int[fpsHistoryCount];

	for (int i = 0; i < fpsHistoryCount; i++)
	{
		this->fpsHistory[i] = 0;
	}

	// switch which gamestate is the startup one
#ifdef DEBUG_9999
	gameState = new GSMenu::State(*device);
	currentState = GS_MENU;
#else
	gameState = new GSMenu::State(*device);
	currentState = GS_MENU;
#endif
}

void BrickGame::run()
{
	SDL_Event ev;

	while (!quitting)
	{
		if (doReset)
		{
			doReset = false;
			gameState->nextState = GS_MENU;
			device->paused = false;
			device->reset();
		}

		this->gameLoopStartTicks = SDL_GetTicks();

		if (gameState->nextState != GS_NONE)
		{
			handleNextGameState(gameState->nextState);
		}

		while (SDL_PollEvent(&ev) != 0)
		{
			processEvent(ev);
		}

		if (doReset)
		{
			continue;
		}

		if (!isMinimized)
		{
			// parse game keys
			if (!device->paused)
			{
				checkKeyboardState();
				gameState->postEvents(*device);
			}
			render();
			deviceTick();
		}

		this->gameLoopEndTicks = SDL_GetTicks();

		updateWindowTitle();
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

void BrickGame::updateWindowTitle() const
{
	// form window title
	char title[255];

	if (isMinimized)
	{
		sprintf_s(title, "BrickGame-9999 (paused)");
	}
	else
	{
		if (gameLoopEndTicks - gameLoopStartTicks != 0)
		{
			for (int i = 0; i < fpsHistoryCount - 1; i++)
			{
				this->fpsHistory[i] = this->fpsHistory[i + 1];
			}
			this->fpsHistory[fpsHistoryCount - 1] = int(1000.0 / float(gameLoopEndTicks - gameLoopStartTicks));

			int sum = 0;
			double average = 0.0;
			for (int i = 0; i < fpsHistoryCount; i++)
			{
				sum = sum + fpsHistory[i];
			}

			average = sum / fpsHistoryCount;
			sprintf_s(title, "BrickGame-9999 FPS:%d", lround(average));
		}
		else
		{
			sprintf_s(title, "BrickGame-9999 FPS:1000+");
		}
	}

	SDL_SetWindowTitle(res->getWindow(), reinterpret_cast<char*>(&title));
}

void BrickGame::setWindowScale(int scale) const
{
	SDL_SetWindowSize(res->getWindow(), res->windowSize.w * scale, res->windowSize.h * scale);
	SDL_RenderSetScale(r, static_cast<float>(scale), static_cast<float>(scale));
}

void BrickGame::setFullscreen(bool isFullscreen)
{
	this->fullscreen = isFullscreen;

	if (isFullscreen)
	{
		l.log(Logger::INFO, "Initializing fullScreen mode");

		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) < 0)
		{
			throw string("Failed retrieve display mode.");
		}

		SDL_SetWindowSize(this->w, displayMode.w, displayMode.h);
		SDL_SetWindowFullscreen(this->w, SDL_WINDOW_FULLSCREEN);
		l.log("Setting window size to: %dx%d (fullscreen)", displayMode.w, displayMode.h);
	}
	else
	{
		SDL_SetWindowFullscreen(this->w, 0);
		SDL_SetWindowSize(this->w, res->windowSize.w * windowScale, res->windowSize.h * windowScale);
		l.log("Setting window size to: %dx%d (windowed)", res->windowSize.w * windowScale, res->windowSize.h * windowScale);
	}
}
