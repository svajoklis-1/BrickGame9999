#pragma once

#include "Types.hpp"
#include "Ticker.hpp"

namespace GSDefend
{
	class Bullet
	{
	public:
		Bullet(Direction dir, int x, int y);
		void tick();
		point getPosition();

	private:
		Ticker t;
		moving_point pos;
	};
}
