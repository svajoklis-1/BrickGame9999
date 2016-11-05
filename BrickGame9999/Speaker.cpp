#include "Speaker.h"

Speaker::Speaker(SoundPlayer *soundPlayer)
{
	this->pl = soundPlayer;
	this->ownSoundPlayer = false;
}

Speaker::~Speaker()
{
	if (this->ownSoundPlayer)
	{
		delete this->pl;
	}
}

void Speaker::playSound(Sound sound)
{
	if (muted)
	{
		return;
	}

	switch (sound) {
	case SND_BLIP:
	case SND_BOUNCE:
	case SND_EXPLODE:
		this->pl->playSound(sound);
		break;

	default:
		break;
	}
}

void Speaker::setMuted(bool muted)
{
	this->muted = muted;
}

bool Speaker::isMuted() const
{
	return muted;
}