#include "GSArkanoid.hpp"
#include "GSArkanoid_Ball.hpp"
#include "Global.hpp"

namespace GSArkanoid
{
	void Ball::setSpeed(int deviceSpeed)
	{
		this->speed = 10 - deviceSpeed;
		this->t.setLength(this->speed);
	}

	void Ball::reset()
	{
		x = 5;
		y = 18;
		dx = 1;
		dy = -1;

		t.reset();
	}

	void Ball::tick(Device &dev, State &s)
	{
		if (t.triggered())
		{
			t.reset();

			if (s.p.isMoving() && dy == 1 && y == (logicalScreen.h - 2) && (x >= s.p.getX() && x <= s.p.getX() + s.p.getW() - 1) && !s.slid)
			{
				dev.speaker.playSound(SND_BOUNCE);

				this->setX(this->getX() + s.p.getDX());
				this->setDY(-this->getDY());

				s.slid = true;
			}
			else
			{
				bool clearedBlock = false;
				bool hitPaddle = false;

				while (true)
				{
					// detection with walls
					if (x == logicalScreen.w - 1 && dx > 0 || x == 0 && dx < 0)
					{
						this->setDX(-this->getDX());
						continue;
					}
					if (y == logicalScreen.h - 1 && dy > 0 || y == 0 && dy < 0)
					{
						this->setDY(-this->getDY());
						continue;
					}

					// detection with paddle
					// block below
					if (y == (logicalScreen.h - 2) && (x >= s.p.getX() && x <= s.p.getX() + s.p.getW() - 1) && (dy > 0))
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						continue;
					}
					// diagonal from left
					if (y == (logicalScreen.h - 2) && (x == s.p.getX() - 1) && (dx > 0) && (dy > 0) && !s.slid)
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						this->setDX(-this->getDX());
						continue;
					}
					// diagonal from right
					if (y == (logicalScreen.h - 2) && (x == s.p.getX() + s.p.getW()) && (dx < 0) && (dy > 0) && !s.slid)
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						this->setDX(-this->getDX());
						continue;
					}

					// detection with level
					if (s.isBlockOccupied(dev, (y + dy) * logicalScreen.w + x))
					{
						s.clearBlock(dev, (y + dy) * logicalScreen.w + x);
						this->setDY(-this->getDY());
						clearedBlock = true;
						continue;
					}

					if (s.isBlockOccupied(dev, (y) * (logicalScreen.w) + x + dx))
					{
						s.clearBlock(dev, y * logicalScreen.w + x + dx);
						this->setDX(-this->getDX());
						clearedBlock = true;
						continue;
					}

					// only collide diagonally if clear on vertical/horizontal

					if (s.isBlockOccupied(dev, (y + dy) * (logicalScreen.w) + x + dx))
					{
						s.clearBlock(dev, (y + dy) * (logicalScreen.w) + x + dx);
						this->setDY(-this->getDY());
						this->setDX(-this->getDX());
						clearedBlock = true;
						continue;
					}

					break;
				}

				if (clearedBlock)
				{
					dev.speaker.playSound(SND_BLIP);
				}
				else if (hitPaddle)
				{
					dev.speaker.playSound(SND_BOUNCE);
				}

				this->setX(this->getX() + this->getDX());
				this->setY(this->getY() + this->getDY());

				s.slid = false;
			}

		}
		else
		{
			t.tick();
		}
	}

	int Ball::getX() const
	{
		return x;
	}

	int Ball::getY() const
	{
		return y;
	}

	int Ball::getDX() const
	{
		return dx;
	}

	int Ball::getDY() const
	{
		return dy;
	}

	void Ball::setX(int x)
	{
		if (x < 0)
		{
			this->x = 0;
			return;
		}

		if (x >= logicalScreen.w)
		{
			this->x = logicalScreen.w - 1;
			return;
		}

		this->x = x;
	}

	void Ball::setY(int y)
	{
		if (y < 0)
		{
			this->y = 0;
			return;
		}

		if (y >= logicalScreen.h)
		{
			this->y = logicalScreen.h - 1;
			return;
		}

		this->y = y;
	}

	void Ball::setDX(int dx)
	{
		this->dx = dx;
	}

	void Ball::setDY(int dy)
	{
		this->dy = dy;
	}

	void Ball::setSpeeding(bool isSpeeding)
	{
		this->speeding = isSpeeding;
		t.setLength(isSpeeding ? speedingSpeed : speed);
	}

	bool Ball::isSpeeding() const
	{
		return this->speeding;
	}
}
