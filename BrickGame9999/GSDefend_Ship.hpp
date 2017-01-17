#pragma once

#include "Ticker.hpp"

namespace GSDefend
{
	class Ship
	{
	public:
		Ship();

		void startMoving(int dx);
		void stopMoving();
		void tick();

		int getX() const;

	private:
		Ticker t;
		int x;
		int dx;
		int w;
	};
}
