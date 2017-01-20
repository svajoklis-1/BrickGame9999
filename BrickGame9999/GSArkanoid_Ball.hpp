#pragma once

#include "Ticker.hpp"
#include "Device.hpp"

namespace GSArkanoid
{
	class State;

	class Ball
	{
	public:
		Ball() {};
		void setSpeed(int deviceSpeed);
		void reset();

		void tick(Device &dev, State &s);

		int getX() const;
		int getY() const;
		int getDX() const;
		int getDY() const;

		void setX(int x);
		void setY(int y);
		void setDX(int dx);
		void setDY(int dy);

		bool isSpeeding();
		void setSpeeding(bool isSpeeding);

	private:
		int speed = 10;
		bool speeding;
		int speedingSpeed = 2;
		int x = 5;
		int y = 18;
		int dx = 1;
		int dy = -1;

		Ticker t;
	};
}
