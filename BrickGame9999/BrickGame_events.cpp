#include "BrickGame.h"
#include "GSMenu.h"

void BrickGame::processEvent(SDL_Event &ev)
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

void BrickGame::checkKeyboardState()
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
}