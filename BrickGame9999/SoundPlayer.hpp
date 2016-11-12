#pragma once

/* SDL dependent sound player */

#include "Types.hpp"
#include "ResourceStore.hpp"

class SoundPlayer 
{
public:
	SoundPlayer(ResourceStore *res);
	void playSound(Sound sound);

private:
	ResourceStore *res;
};