#include "GSArkanoid.hpp"
#include "GSArkanoid_Ball.hpp"
#include "Global.hpp"

namespace GSArkanoid
{
	Ball::Ball() :
	pos(5, 18, -1, 1)
	{
		
	}

	void Ball::setSpeed(int deviceSpeed) 
	{
		this->speed = 10 - deviceSpeed;
		this->t.setLength(this->speed);
	}

	void Ball::reset()
	{
		pos.x = 5;
		pos.y = 18;
		pos.dx = 1;
		pos.dy = -1;

		t.reset();
	}

	void Ball::tick(Device &dev, State &s)
	{
		if (t.triggered())
		{
			t.reset();

			if (s.p.isMoving() && pos.dy == 1 && pos.y == (logicalScreen.h - 2) && (pos.x >= s.p.getX() && pos.x <= s.p.getX() + s.p.getW() - 1) && !s.slid)
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
					if (pos.x == logicalScreen.w - 1 && pos.dx > 0 || pos.x == 0 && pos.dx < 0)
					{
						this->setDX(-this->getDX());
						continue;
					}
					if (pos.y == logicalScreen.h - 1 && pos.dy > 0 || pos.y == 0 && pos.dy < 0)
					{
						this->setDY(-this->getDY());
						continue;
					}

					// detection with paddle
					// block below
					if (pos.y == (logicalScreen.h - 2) && (pos.x >= s.p.getX() && pos.x <= s.p.getX() + s.p.getW() - 1) && (pos.dy > 0))
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						continue;
					}
					// diagonal from left
					if (pos.y == (logicalScreen.h - 2) && (pos.x == s.p.getX() - 1) && (pos.dx > 0) && (pos.dy > 0) && !s.slid)
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						this->setDX(-this->getDX());
						continue;
					}
					// diagonal from right
					if (pos.y == (logicalScreen.h - 2) && (pos.x == s.p.getX() + s.p.getW()) && (pos.dx < 0) && (pos.dy > 0) && !s.slid)
					{
						hitPaddle = true;
						this->setDY(-this->getDY());
						this->setDX(-this->getDX());
						continue;
					}

					// detection with level
					if (s.isBlockOccupied(dev, (pos.y + pos.dy) * logicalScreen.w + pos.x))
					{
						s.clearBlock(dev, (pos.y + pos.dy) * logicalScreen.w + pos.x);
						this->setDY(-this->getDY());
						clearedBlock = true;
						continue;
					}

					if (s.isBlockOccupied(dev, (pos.y) * (logicalScreen.w) + pos.x + pos.dx))
					{
						s.clearBlock(dev, pos.y * logicalScreen.w + pos.x + pos.dx);
						this->setDX(-this->getDX());
						clearedBlock = true;
						continue;
					}

					// only collide diagonally if clear on vertical/horizontal

					if (s.isBlockOccupied(dev, (pos.y + pos.dy) * (logicalScreen.w) + pos.x + pos.dx))
					{
						s.clearBlock(dev, (pos.y + pos.dy) * (logicalScreen.w) + pos.x + pos.dx);
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
		return pos.x;
	}

	int Ball::getY() const
	{
		return pos.y;
	}

	int Ball::getDX() const
	{
		return pos.dx;
	}

	int Ball::getDY() const
	{
		return pos.dy;
	}

	void Ball::setX(int x)
	{
		if (x < 0)
		{
			this->pos.setX(0);
			return;
		}

		if (x >= logicalScreen.w)
		{
			this->pos.setX(logicalScreen.w - 1);
			return;
		}

		this->pos.setX(x);
	}

	void Ball::setY(int y)
	{
		if (y < 0)
		{
			this->pos.setY(0);
			return;
		}

		if (y >= logicalScreen.h)
		{
			this->pos.setY(logicalScreen.h - 1);
			return;
		}

		this->pos.setY(y);
	}

	void Ball::setDX(int dx)
	{
		this->pos.setDX(dx);
	}

	void Ball::setDY(int dy)
	{
		this->pos.setDY(dy);
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
