#include "GSDefend_Ship.hpp"
#include "Global.hpp"

namespace GSDefend
{
	Ship::Ship() :
	t(5)
	{
		this->reset();
	}

	void Ship::tick()
	{
		this->t.tick();
		if (this->t.triggered())
		{
			this->t.reset();
			this->x += this->dx;

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

	void Ship::startMoving(int dx)
	{
		this->t.forceTrigger();
		this->dx = dx;
	}

	void Ship::stopMoving()
	{
		this->t.reset();
		this->startMoving(0);
	}

	int Ship::getX() const
	{
		return this->x;
	}

	void Ship::reset()
	{
		this->w = 3;

		this->x = logicalScreen.w / 2;
		this->dx = 0;
	}
}
