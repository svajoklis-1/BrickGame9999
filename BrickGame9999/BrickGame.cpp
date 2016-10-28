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
	bool quitting = false;

	SDL_Event ev;

	while (!quitting)
	{
		int gameLoopStartTicks = SDL_GetTicks();

		if (gameState->nextState != GS_NONE)
		{
			handleNextGameState(gameState->nextState);
		}

		bool doReset = false;

		while (SDL_PollEvent(&ev) != 0)
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				quitting = true;
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				// background changing keys
				case SDL_SCANCODE_F8: device->nextBG(); break;
				case SDL_SCANCODE_F7: device->prevBG(); break;
				case SDL_SCANCODE_KP_PLUS: windowScale++; setWindowScale(windowScale); break;
				case SDL_SCANCODE_KP_MINUS: if (windowScale > 1) windowScale--; setWindowScale(windowScale); break;
				default: break;
				}

				// device keys

				if (ev.key.keysym.scancode == keyMap[KEY_RESET])
				{
					doReset = true;
				}
				else if (ev.key.keysym.scancode == keyMap[KEY_START])
				{
					if (currentState == GS_MENU)
					{
						gameState->nextState = static_cast<GSMenu*>(gameState)->getSelectedState();
					}
					else
					{
						if (device->inGame && device->pauseable)
						{
							device->paused = !device->paused;
							device->screen.paused = !device->screen.paused;
						}
					}
				}

				break;
			}
		}

		// parse game keys

		if (!device->paused)
		{
			const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

			for (int i = KEY_UP; i <= KEY_ACTION; i++)
			{
				if (keyboardState[keyMap[i]] != prevKeyboardState[i])
				{
					gameState->parseEvent(*device, static_cast<Key>(i), (keyboardState[keyMap[i]] == 0 ? STATE_UP : STATE_DOWN));
				}
					
				prevKeyboardState[i] = keyboardState[keyMap[i]];
			}

			gameState->postEvents(*device);
		}


		render(gameLoopStartTicks);
		deviceTick();

		int gameLoopEndTicks = SDL_GetTicks();

		updateWindowTitle(gameLoopStartTicks, gameLoopEndTicks);

		if (doReset)
		{
			gameState->nextState = GS_MENU;
			device->paused = false;
			device->screen.paused = false;
			device->reset();
		}
	}

	try
	{
		SaveManager::writeSave(windowScale, framerateControl, *device);
	}
	catch (...)
	{
		SaveManager::defaultSave(windowScale, framerateControl, *device);
		throw string("Writing save data failed, reverting to default...\nYour highscores are gone (and probably were gone to start with).");
	}
	
}

void BrickGame::updateWindowTitle(int gameLoopStartTicks, int gameLoopEndTicks)
{
	// form window title
	char title[255];
	if (gameLoopEndTicks - gameLoopStartTicks != 0)
	{
		sprintf_s(title, "BrickGame-9999 FPS:%d", int(1000.0 / (gameLoopEndTicks - gameLoopStartTicks)));
	}
	else
	{
		sprintf_s(title, "BrickGame-9999 FPS:1000+");
	}
	SDL_SetWindowTitle(res->getWindow(), reinterpret_cast<char*>(&title));
}

void BrickGame::setWindowScale(int scale)
{
	SDL_SetWindowSize(res->getWindow(), res->windowSize.w * scale, res->windowSize.h * scale);
	SDL_RenderSetScale(r, static_cast<float>(scale), static_cast<float>(scale));
}