#pragma once

#include "Types.hpp"
#include "Device.hpp"
#include "Ticker.hpp"

class Explosion
{
public:
	Explosion();
	bool hasEnded()
		{ return ended; }

	void render(Device &dev);
	void setCoord(coord where){
		explosionPosition = where; 
		explosionPosition.x -= 1;
		explosionPosition.y -= 1;
	}

private:
	coord explosionPosition;
	bool ended = false;
	Ticker displayTicker;
	string frames[2];
	int currentFrame;
};