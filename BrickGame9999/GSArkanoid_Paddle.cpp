#include "GSArkanoid.hpp"
#include "GSArkanoid_Paddle.hpp"

#include "Global.hpp"
#include "Types.hpp"

namespace GSArkanoid
{
	void Paddle::setX(int x)
	{
		this->x = x;
	}

	void Paddle::reset()
	{
		x = 3;
		dx = 0;
		t.setLength(4);
		t.reset();
	}

	void Paddle::tick(Device &dev, State &s)
	{
		t.tick();
		if (t.triggered())
		{
			t.reset();

			if (dx != 0 && s.b.getDY() == 1 && s.b.getY() == (logicalScreen.h - 2) && (s.b.getX() >= x && s.b.getX() <= x + w - 1) && !s.slid)
			{
				s.b.setX(s.b.getX() + dx);
				s.b.setDY(-s.b.getDY());

				s.slid = true;

				dev.speaker.playSound(SND_BOUNCE);
			}

			x += dx;
			if (x < 0)
				x = 0;
			if (x > 10 - w)
				x = 10 - w;

		}
	}

	void Paddle::startMoving(int dx)
	{
		t.forceTrigger();
		this->dx = dx;
	}

	int Paddle::getX() const
	{
		return x;
	}

	int Paddle::getDX() const
	{
		return dx;
	}

	int Paddle::getW() const
	{
		return w;
	}

	bool Paddle::isMoving() const
	{
		return dx != 0;
	}

	bool Paddle::isMoving(Direction d) const
	{
		switch (d)
		{
		case DIR_LEFT:
			return dx < 0;
		case DIR_RIGHT:
			return dx > 0;
		default:
			return false;
		}
	}
}
