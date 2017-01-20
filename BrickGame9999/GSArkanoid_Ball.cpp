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

			if (s.p.getDX() != 0 && dy == 1 && y == (logicalScreen.h - 2) && (x >= s.p.getX() && x <= s.p.getX() + s.p.getW() - 1) && !s.slid)
			{
				dev.speaker.playSound(SND_BOUNCE);
				x += s.p.getDX();
				if (x < 0)
				{
					x = 0;
				}
				else
					if (x >= logicalScreen.w)
					{
						x = logicalScreen.w - 1;
					}

				dy = -dy;

				s.slid = true;
			}
			else
			{
				/*while (true)
				{
					
				}*/

				if (x == logicalScreen.w - 1 || x == 0)
				{
					dx = -dx;
				}
				if (y == 0 || y == logicalScreen.h - 1)
				{
					dy = -dy;
				}

				// hit detection with paddle
				// block below
				if (y == (logicalScreen.h - 2) && (x >= s.p.getX() && x <= s.p.getX() + s.p.getW() - 1) && (dy == 1))
				{
					dev.speaker.playSound(SND_BOUNCE);
					dy = -dy;
				}
				else // diagonal from left
				if (y == (logicalScreen.h - 2) && (x == s.p.getX() - 1) && (dx == 1) && (dy == 1) && !s.slid)
				{
					dev.speaker.playSound(SND_BOUNCE);
					dy = -dy;
					dx = -dx;
				}
				else // diagonal from right
				if (y == (logicalScreen.h - 2) && (x == s.p.getX() + s.p.getW()) && (dx == -1) && (dy == 1) && !s.slid)
				{
					dev.speaker.playSound(SND_BOUNCE);
					dy = -dy;
					dx = -dx;
				}

				int newBallDX = dx;
				int newBallDY = dy;

				bool clearedBlock = false;

				do
				{
					dx = newBallDX;
					dy = newBallDY;

					// collision with level
					bool collidedWithLevel = false;
					// on y

					if (s.isBlockOccupied(dev, (y + dy) * logicalScreen.w + x))
					{
						s.clearBlock(dev, (y + dy) * logicalScreen.w + x);
						newBallDY = -dy;
						collidedWithLevel = true;
						clearedBlock = true;
					}

					if (s.isBlockOccupied(dev, (y) * (logicalScreen.w) + x + dx))
					{
						s.clearBlock(dev, y * logicalScreen.w + x + dx);
						newBallDX = -dx;
						collidedWithLevel = true;
						clearedBlock = true;
					}

					// only collide diagonally if clear on vertical/horizontal

					if (!collidedWithLevel && s.isBlockOccupied(dev, (y + dy) * (logicalScreen.w) + x + dx))
					{
						s.clearBlock(dev, (y + dy) * (logicalScreen.w) + x + dx);
						newBallDY = -dy;
						newBallDX = -dx;
						collidedWithLevel = true;
						clearedBlock = true;
					}

				} while (newBallDX != dx || newBallDY != dy);

				if (clearedBlock) {
					dev.speaker.playSound(SND_BLIP);
				}

				dx = newBallDX;
				dy = newBallDY;

				if (x + dx < 0 || x + dx >= (logicalScreen.w))
				{
					dev.speaker.playSound(SND_BLIP);
					dx = -dx;
				}

				if (y + dy < 0 || y + dy >= (logicalScreen.h))
				{
					dev.speaker.playSound(SND_BLIP);
					dy = -dy;
				}

				x += dx;
				y += dy;

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

	bool Ball::isSpeeding()
	{
		return this->speeding;
	}
}
