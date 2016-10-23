#pragma once

/* SDL dependent sound player */

#include "Types.h"
#include "ResourceStore.h"

class SoundPlayer 
{
public:
	SoundPlayer(ResourceStore *res);
	void playSound(Sound sound);

private:
	ResourceStore *res;
};