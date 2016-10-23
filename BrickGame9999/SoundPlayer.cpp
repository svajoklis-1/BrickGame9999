#include "SoundPlayer.h"

#include <iostream>

SoundPlayer::SoundPlayer(ResourceStore *res)
{
	this->res = res;

	Mix_AllocateChannels(16);
	Mix_Volume(-1, 96);
}

void SoundPlayer::playSound(Sound sound)
{
	std::cout << "Playing sound [" << sound << "]";
	switch (sound)
	{
	case SND_BLIP:
		Mix_PlayChannel(0, res->snd("blip.wav"), 0);
		break;
	case SND_EXPLODE:
		Mix_PlayChannel(0, res->snd("explode.wav"), 0);
		break;
	case SND_BOUNCE:
		Mix_PlayChannel(0, res->snd("bounce.wav"), 0);
		break;
	detault:
		break;
	}
}