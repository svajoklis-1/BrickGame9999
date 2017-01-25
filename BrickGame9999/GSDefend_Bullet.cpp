#include "GSDefend_Bullet.hpp"

namespace GSDefend
{
	Bullet::Bullet(Direction dir, int x, int y) :
		t(2),
		pos(x, y, dxOfDirection(dir), dyOfDirection(dir))
	{
	}

	void Bullet::tick()
	{
		if (t.triggered())
		{
			t.reset();
			this->pos.moveByDelta();
		}
		else
		{
			t.tick();
		}
	}

	point Bullet::getPosition()
	{
		return this->pos.toPoint();
	}

}