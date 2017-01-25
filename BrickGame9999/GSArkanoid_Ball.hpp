#pragma once

#include "Ticker.hpp"
#include "Device.hpp"

namespace GSArkanoid
{
	class State;

	class Ball
	{
	public:
		Ball();
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

		bool isSpeeding() const;
		void setSpeeding(bool isSpeeding);

	private:
		int speed = 10;
		bool speeding = false;
		int speedingSpeed = 2;

		moving_point pos = moving_point(5, 18, 1, -1);

		Ticker t;
	};
}
