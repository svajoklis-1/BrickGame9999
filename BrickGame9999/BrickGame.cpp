#include "BrickGame.h"
#include "GSGameOver.h"
#include <boost/foreach.hpp>
#include <vector>

using namespace std;

BrickGame::BrickGame()
{
	/***************************************************************** LOAD SETTINGS */

	readSave();

	/****************************/

	res = new ResourceStore(scrRect);
	bgRenderer = new BackgroundRenderer(scrRect);
	scRenderer = new ScreenRenderer();

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw string("Could not initialize SDL!\nSDL_Error: " + string(SDL_GetError()));

	if(IMG_Init(IMG_INIT_PNG) < 0)
		throw string("Failed to init SDL_Image!");

	w = SDL_CreateWindow("9999-in-1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res->windowSize.w * windowScale, res->windowSize.h * windowScale, SDL_WINDOW_SHOWN);
	if (!w)
		throw string("Failed to create SDL window.");

	if (framerateControl == FRC_VSYNC)
	{
		r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_RenderSetScale(r, windowScale, windowScale);
	}
	else
	{
		r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetScale(r, windowScale, windowScale);
	}

	icon = nullptr;
	icon = IMG_Load("Resources\\icon.png");

	if (icon == nullptr)
		throw string("Unable to load image icon.png!\nSDL_image Error: ") + IMG_GetError();

	SDL_SetWindowIcon(w, icon);

	if (!r)
		throw string("Failed to create SDL renderer.");

	res->location["screen"] = { 46, 18 };
	res->location["hint"] = { 149, 81 };
	res->location["score"] = { 181, 28 };
	res->location["hiscore"] = { 181, 58 };

	res->location["level"] = { 161, 149 };
	res->location["speed"] = { 161, 131 };

	res->item["screenPixel"] = { 1, 1, 8, 8 };
	res->item["hintPixel"] = { 10, 1, 7, 7 };
	res->item["note"] = { 18, 1, 11, 14 };
	res->item["screenPixelShadow"] = { 1, 10, 8, 8 };

	res->item["digit"] = { 0, 0, 7, 15 };

	res->setWindow(w);
	res->setRenderer(r);

	device.screen.highScore.dash();
	device.screen.score.dash();
	device.screen.level.dash();
	device.screen.level.setLink(&device.stage);
	device.screen.speed.dash();
	device.screen.level.setLink(&device.stage);

	// switch which gamestate is the startup one
#ifdef DEBUG_9999
		gameState = new GSMenu(device);
		currentState = GS_MENU;
#else
		gameState = new GSMenu(device);
		currentState = GS_MENU;
#endif
}

template <typename T>
std::vector<T> as_vector(pt::ptree const& pt, pt::ptree::key_type const& key)
{
	std::vector<T> r;
	for (auto& item : pt.get_child(key))
		r.push_back(item.second.get_value<T>());
	return r;
}

void BrickGame::readSave()
{
	pt::ptree saveFile;
	
	unsigned int magic;

	try
	{
		pt::read_ini("saveData.ini", saveFile);
		magic = saveFile.get<unsigned int>("magic.magic", magicVal);

		windowScale = saveFile.get<int>("window.scale", 1);
		framerateControl = saveFile.get<int>("window.frameControl", 2);

		device.setBGCount(saveFile.get<int>("device.backgroundCount", 14));
		device.setBG(saveFile.get<int>("device.currentBackground", 1) - 1);

		try
		{
			BOOST_FOREACH(pt::ptree::value_type &v, saveFile.get_child("highScore"))
			{
				cout << v.first.c_str()[0] << " : " << v.second.get_value<int>();
				device.highScore[v.first.c_str()[0]] = v.second.get_value<int>();
			}
		}
		catch (...)
		{
			cout << "highScore not found!" << endl;
		}

		cout << endl;
	}
	catch (...)
	{
		defaultSave();
		throw string("saveData read failed, reverting to defaults...\nRestart and try again");
	}
	
	cout << "Magic: " << magic << endl;
	if (magic != calcMagic())
	{
		defaultSave();
		throw string("saveData corrupted, reverting...\nRestart and try again");
	}
}

unsigned int BrickGame::calcMagic()
{
	unsigned int magic = magicVal;

	for (auto iterator = device.highScore.begin(); iterator != device.highScore.end(); ++iterator)
	{
		if ((unsigned)iterator->second != 0)
			magic ^= (unsigned)iterator->second;
	}

	return magic;
}

void BrickGame::writeSave()
{
	pt::ptree saveFile;
	pt::read_ini("saveData.ini", saveFile);

	saveFile.put("window.scale", windowScale);
	saveFile.put("window.frameControl", framerateControl);

	saveFile.put("device.currentBackground", device.getCurrentBG() + 1);
	
	for (auto iterator = device.highScore.begin(); iterator != device.highScore.end(); ++iterator)
	{
		string key;
		key.append("highScore.");
		key.push_back(iterator->first);
		cout << iterator->first << " : " << iterator->second << endl;
		saveFile.put<int>(key, device.highScore[iterator->first]);
	}

	saveFile.put("magic.magic", calcMagic());

	pt::write_ini("saveData.ini", saveFile);
}

void BrickGame::defaultSave()
{
	pt::ptree saveFile;

	saveFile.put("window.scale", windowScale);
	saveFile.put("window.frameControl", framerateControl);
	
	saveFile.put("device.backgroundCount", device.getBGCount());
	saveFile.put("device.currentBackground", device.getCurrentBG() + 1);

	pt::write_ini("saveData.ini", saveFile);
}

BrickGame::~BrickGame()
{
	delete res;
	delete bgRenderer;
	delete scRenderer;

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);

	IMG_Quit();
	SDL_Quit();
}

void BrickGame::run()
{
	bool quitting = false;

	SDL_Event ev;

	int tickLimiter = SDL_GetTicks();

	bool paused = false;

	while (!quitting)
	{
		int ticksBefore = SDL_GetTicks();

		if (gameState->nextState != GS_NONE)
		{
			GameStates next = gameState->nextState;
			delete gameState;

			switch (next)
			{
			case GS_MENU:
				gameState = new GSMenu(device);
				currentState = GS_MENU;
				break;

			case GS_RAIN:
				gameState = new GSRain(device);
				currentState = GS_RAIN;
				break;

			case GS_SNAKE:
				gameState = new GSSnake(device);
				currentState = GS_SNAKE;
				break;

			case GS_GAMEOVER:
				gameState = new GSGameOver(device, GS_MENU);
				currentState = GS_GAMEOVER;
				break;

			case GS_GAMEOVER_TOCURRENT:
				gameState = new GSGameOver(device, currentState);
				currentState = GS_GAMEOVER_TOCURRENT;
				break;

			default:
				gameState = new GSMenu(device);
				break;
			}

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
				case SDL_SCANCODE_F8:
					device.nextBG();
					break;

				case SDL_SCANCODE_F7:
					device.prevBG();
					break;

				// technical keys
				case SDL_SCANCODE_F1:
					doReset = true;
					break;

				case SDL_SCANCODE_KP_PLUS:
					windowScale++;
					setWindowScale(windowScale);
					break;

				case SDL_SCANCODE_KP_MINUS:
					if (windowScale > 1)
						windowScale--;
					setWindowScale(windowScale);
					break;

				case SDL_SCANCODE_KP_DIVIDE:
					paused = !paused;
					break;

				default:
					break;
				}

				if (!paused)
				switch (ev.key.keysym.scancode)
				{
					// actual device keys
					case SDL_SCANCODE_UP:
						gameState->parseEvent(device, KEY_UP);
						break;

					case SDL_SCANCODE_DOWN:
						gameState->parseEvent(device, KEY_DOWN);
						break;

					case SDL_SCANCODE_LEFT:
						gameState->parseEvent(device, KEY_LEFT);
						break;

					case SDL_SCANCODE_RIGHT:
						gameState->parseEvent(device, KEY_RIGHT);
						break;

					case SDL_SCANCODE_SPACE:
						gameState->parseEvent(device, KEY_ACTION);
						break;

					default: break;
				}

				break;
			}
		}

		// render background
		bgRenderer->render(*res, device.getCurrentBG());

		// if tick is ok or framerate is vsynced
		if ((SDL_GetTicks() - tickLimiter) > (1000.f / 60.f) || (framerateControl == FRC_VSYNC))
		{
			tickLimiter = SDL_GetTicks();
			if (!paused)
				gameState->tick(device);

			// let the game render on the device
			gameState->render(device);

			scRenderer->moveShadows();
		}

		scRenderer->render(device.screen, *res);

		SDL_RenderPresent(res->getRenderer());

		// framerate limit
		int ticksNow = SDL_GetTicks();

		int fps = 250;
		if ((ticksNow - ticksBefore) < (1000 / fps) && (framerateControl == FRC_250))
		{
			SDL_Delay((1000 / fps) - (ticksNow - ticksBefore));
			ticksNow = SDL_GetTicks();
		}

		// form window title
		char title[255];
		if (ticksNow - ticksBefore != 0)
		{
			sprintf_s(title, "BrickGame-9999 FPS:%d, limit:%d", int(1000.0 / (ticksNow - ticksBefore)), framerateControl);
		}
		else
		{
			sprintf_s(title, "BrickGame-9999 FPS:1000+, limit:%d", framerateControl);
		}
		SDL_SetWindowTitle(res->getWindow(), (char*)&title);

		if (doReset)
		{
			gameState->nextState = GS_MENU;
			device.reset();
		}
	}

	try
	{
		writeSave();
	}
	catch (...)
	{
		defaultSave();
		throw string("Writing save data failed, reverting to default...\nYour highscores are gone (and probably were gone to start with).");
	}
	
}

void BrickGame::setWindowScale(int scale)
{
	SDL_SetWindowSize(res->getWindow(), res->windowSize.w * scale, res->windowSize.h * scale);
	SDL_RenderSetScale(r, (float)scale, (float)scale);
}