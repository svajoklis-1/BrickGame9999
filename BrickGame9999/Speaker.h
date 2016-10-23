#pragma once

/* A device Speaker that is able to play sounds. Delegates actual sound playing to a SoundPlayer class */

#include "Types.h"
#include "SoundPlayer.h"

class Speaker
{
public:
	Speaker::Speaker(SoundPlayer *soundPlayer);
	~Speaker();
	
	void playSound(Sound sound);

private:
	SoundPlayer *pl;
	bool ownSoundPlayer = false;
};