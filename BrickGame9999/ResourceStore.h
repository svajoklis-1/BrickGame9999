#pragma once

#include <SDL.h>
#include <map>
#include <SDL_mixer.h>

#include "Types.h"

using namespace std;

// a class to store and manage resource loading
// an easier way to pass down resources

class ResourceStore
{
public:
	ResourceStore(SDL_Rect windowSize);
	~ResourceStore();

	void setWindow(SDL_Window *w);
	void setRenderer(SDL_Renderer *r);

	SDL_Rect windowSize;

	SDL_Window *getWindow();
	SDL_Renderer *getRenderer();
	SDL_Texture *img(string name);
	Mix_Chunk *snd(string name);

	map<string, coord> location;
	map<string, SDL_Rect> item;

private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	map<string, SDL_Texture *> imageMap;
	map<string, Mix_Chunk *> soundMap;

	SDL_Texture *loadTexture(string path);
	Mix_Chunk *loadSound(string path);
};