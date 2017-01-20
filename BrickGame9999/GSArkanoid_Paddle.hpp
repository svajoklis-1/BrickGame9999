#pragma once

#include "Ticker.hpp"
#include "Device.hpp"

namespace GSArkanoid
{
	class State;

	class Paddle
	{
	public:
		Paddle() {};

		void setX(int x);
		void reset();

		void tick(Device &dev, State &s);

		int getX() const;
		int getDX() const;
		int getW() const;

		bool isMoving() const;
		bool isMoving(Direction d) const;

		void startMoving(int dx);

	private:
		int x = 3;
		int dx = 0;

		int w = 4;

		Ticker t;
	};
}
