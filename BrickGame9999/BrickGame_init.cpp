#include "BrickGame.h"

#include <SDL_image.h>
#include <SDL_mixer.h>

void BrickGame::initSystem()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw string("Could not initialize SDL.\nSDL_Error: " + string(SDL_GetError()));
	}

	l.log(Logger::INFO, "SDL Init^r[OK]");

	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		throw string("Failed to init SDL_Image.");
	}

	l.log(Logger::INFO, "IMG Init^r[OK]");

	if (Mix_Init(0) < 0)
	{
		throw string("Failed to initialize SDL_Mixer.");
	}

	l.log(Logger::INFO, "MIX Init^r[OK]");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) < 0)
	{
		throw string("Failed to open audio for SDL_Mixer.");
	}

	l.log(Logger::INFO, "Mix_OpenAudio^r[OK]");

	w = SDL_CreateWindow("9999-in-1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res->windowSize.w * windowScale, res->windowSize.h * windowScale, SDL_WINDOW_SHOWN);
	if (!w)
	{
		throw string("Failed to create SDL window.");
	}

	l.log(Logger::INFO, "Creating SDL window...^r[OK]");

	if (framerateControl == FRC_VSYNC)
	{
		r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_RenderSetScale(r, static_cast<float>(windowScale), static_cast<float>(windowScale));
	}
	else
	{
		r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetScale(r, static_cast<float>(windowScale), static_cast<float>(windowScale));
	}

	l.log(Logger::INFO, "Creating SDL renderer...^r[OK]");

	icon = IMG_Load("Resources\\icon.png");

	if (icon == nullptr)
	{
		throw string("Unable to load image icon.png.\nSDL_image Error: ") + IMG_GetError();
	}

	l.log(Logger::INFO, "Loading icon...^r[OK]");

	SDL_SetWindowIcon(w, icon);

	if (!r)
	{
		throw string("Failed to create SDL renderer.");
	}

	res->setWindow(w);
	res->setRenderer(r);
}

void BrickGame::deinitSystem()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

void BrickGame::initDevice()
{
	device->screen.highScore.dash();
	device->screen.score.dash();
	device->screen.level.setLink(&device->stage);
	device->screen.speed.setLink(&device->stage);
}

BrickGame::~BrickGame()
{
	delete res;
	delete bgRenderer;
	delete scRenderer;
	delete soundPlayer;

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);

	deinitSystem();
}