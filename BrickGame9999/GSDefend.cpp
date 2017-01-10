#include "GSDefend.hpp"

namespace GSDefend
{
	void State::tick(Device &dev)
	{
		
	}

	void State::render(Device &dev)
	{
		
	}

	void State::parseEvent(Device &dev, Key k, KeyState ks)
	{
		switch (k)
		{
		case KEY_LEFT:
			ship.move(-1);
			break;

		case KEY_RIGHT:
			ship.move(1);
			break;
		}
	}
}