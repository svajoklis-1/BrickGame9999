#include "GSDefend_Ship.hpp"
#include "Global.hpp"

namespace GSDefend
{
	Ship::Ship()
	{
		this->w = 3;
		this->x = logicalScreen.w / 2;
	}

	void Ship::move(int cells)
	{
		this->x += cells;

		if (this->x >= logicalScreen.w)
		{
			this->x = logicalScreen.w - 1;
		}
		else if (this->x < 0)
		{
			this->x = 0;
		}
	}
}
