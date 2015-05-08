#include "BrickGame.h"
#include "GSGameOver.h"

BrickGame::BrickGame() :
device(14)
{
	SDL_Rect scrRect = { 0, 0, 233, 215 };

	res = new ResourceStore(scrRect);
	bgRenderer = new BackgroundRenderer(scrRect);
	scRenderer = new ScreenRenderer();

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw string("Could not initialize SDL!\nSDL_Error: " + string(SDL_GetError()));

	if(IMG_Init(IMG_INIT_PNG) < 0)
		throw string("Failed to init SDL_Image!");

	w = SDL_CreateWindow("9999-in-1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res->windowSize.w, res->windowSize.h, SDL_WINDOW_SHOWN);
	if (!w)
		throw string("Failed to create SDL window.");

	r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

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

	gameState = new GSGameOver(device, GS_MENU);
	currentState = GS_MENU;
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
			// space - action
			// arrows - arrows

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

				case SDL_SCANCODE_F1:
					doReset = true;
					break;

				default:
					break;

				}
			}
		}

		gameState->tick(device);

		// render background
		bgRenderer->render(*res, device.getCurrentBG());

		scRenderer->render(device.screen, *res);

		SDL_RenderPresent(res->getRenderer());

		// framerate limit
		int ticksNow = SDL_GetTicks();

		int fps = 60;
		if ((ticksNow - ticksBefore) < (1000 / fps))
		{
			char title[255];
			if (ticksNow - ticksBefore != 0)
			{
				sprintf_s(title, "9999-in-1, FPS:%d", int(1000 / (ticksNow - ticksBefore)));
			}
			else
			{
				sprintf_s(title, "9999-in-1, FPS:1000+");
			}

			SDL_SetWindowTitle(res->getWindow(), (char*)&title);
			SDL_Delay((1000 / fps) - (ticksNow - ticksBefore));
		}

		if (doReset)
		{
			gameState->nextState = GS_MENU;
			device.reset();
		}
	}
}