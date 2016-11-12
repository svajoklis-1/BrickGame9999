#pragma once

#include "Types.hpp"
#include "Ticker.hpp"
#include "Device.hpp"

namespace GSSnake
{
	class Snake
	{
	public:
		enum dirs
		{
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		Snake(Device &dev);

		void reset(Device &dev);

		void parseEvent(Key k, KeyState state);
		void tick(Device &dev);
		void render(Device &dev);

		int setSpeedBySpeed(int newSpeed);

		int getLength() { return length; }
		coord getSegment(int index);
		void setLength(int length) { this->length = length; }
		int getSpeed() { return speed; }

		bool isSpeeding() { return speeding; }

		coord getHead();
		bool doesCollide(coord c);

	private:

		coord segments[256];
		int length = 3;
		int speed = 15;
		
		bool didTurn = false;
		bool speeding = false;

		int snakeHeadX, snakeHeadY;
		int dir = RIGHT;

		Ticker snakeHeadBlinkTicker;
	};
}
