#include "ResourceStore.h"

void ResourceStore::setWindow(SDL_Window *w)
{
	if (window == nullptr)
	{
		window = w;
	}
}

void ResourceStore::setRenderer(SDL_Renderer *r)
{
	if (renderer == nullptr)
	{
		renderer = r;
	}
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

SDL_Texture *ResourceStore::loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;

	// load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		throw string("Unable to load image " + path + "!\nSDL_image Error: " + IMG_GetError());

	// create texture from surface
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
		throw string("Unable to create texture from " + path + "!\nSDL Error: " + IMG_GetError());

	// free old surface (no longer needed)
	SDL_FreeSurface(loadedSurface);

	return newTexture;
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