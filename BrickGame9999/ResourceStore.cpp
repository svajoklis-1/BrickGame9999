#include "ResourceStore.hpp"
#include <SDL_image.h>

#include "Global.hpp"

void ResourceStore::setWindow(SDL_Window *w)
{
	window = w;
}

void ResourceStore::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

SDL_Window *ResourceStore::getWindow()
{
	return window;
}

SDL_Renderer *ResourceStore::getRenderer()
{
	return renderer;
}

SDL_Texture *ResourceStore::img(string name)
{
	if (imageMap.find(name) == imageMap.end())
	{
		imageMap[name] = loadTexture("Resources\\" + name);
	}

	return imageMap[name];
}

Mix_Chunk *ResourceStore::snd(string name)
{
	if (soundMap.find(name) == soundMap.end())
	{
		soundMap[name] = loadSound("Resources\\" + name);
	}

	return soundMap[name];
}

SDL_Texture *ResourceStore::loadTexture(string path)
{
	SDL_Texture* newTexture;

	// load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		l.log(Logger::ERR, "Failed to load image: %s", path.c_str());
		throw string("Unable to load image " + path + "!\nSDL_Image Error: " + IMG_GetError());
	}
		

	// create texture from surface
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == nullptr)
	{
		l.log(Logger::ERR, "Failed to create texture from image: %s", path.c_str());
		throw string("Unable to create texture from " + path + "!\nSDL Error: " + IMG_GetError());
	}

	// free old surface (no longer needed)
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

Mix_Chunk *ResourceStore::loadSound(string path)
{
	Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());

	if (!chunk)
	{
		l.log(Logger::ERR, "Failed to load sound: %s", path.c_str());
		throw string("Unable to load sound " + path + "!\nSDL_Mixer Error: " + Mix_GetError());
	}

	return chunk;
}

ResourceStore::ResourceStore(SDL_Rect windowSize)
{
	this->windowSize = windowSize;
}

ResourceStore::~ResourceStore()
{
	for (auto it = imageMap.begin(); it != imageMap.end();)
	{
		SDL_DestroyTexture((it->second));
		it = imageMap.erase(it);
	}
}