#include "GSDefend.hpp"

namespace GSDefend
{

	State::State(Device &dev)
	{
		this->shipExploded = false;
		this->shipExplodedPause.setLength(60);
	}

	void State::tick(Device &dev)
	{
		if (!this->shipExploded)
		{
			this->level.tick();
			this->ship.tick();
		}
		else
		{
			if (!this->shipExplodedPause.triggered())
			{
				this->shipExplodedPause.tick();
			}
			else
			{
				nextState = GS_GAMEOVER_TOCURRENT;
			}
		}

		if (this->level.getCurrentHeight() >= logicalScreen.h)
		{
			ex.setCoord({ this->ship.getX(), logicalScreen.h - 1 });
			this->shipExploded = true;
		}
	}

	void State::render(Device &dev)
	{
		Screen &s = dev.screen;
		s.clear();

		for (int x = 0; x < this->level.getWidth(); x++)
		{
			for (int y = 0; y < this->level.getHeight(); y++)
			{
				s.mainArray.setPixel(x, y, level.getXY(x, y) ? PXARRAY_ON : PXARRAY_OFF);
			}
		}

		s.mainArray.setPixel(this->ship.getX(), logicalScreen.h - 1, PXARRAY_ON);

		if (this->shipExploded)
		{
			this->ex.render(dev);
		}
	}

	void State::parseEvent(Device &dev, Key k, KeyState ks)
	{
		if (key_pressed(ks))
		{
			switch (k)
			{
			case KEY_LEFT:
				this->keysPressed += 1;
				ship.startMoving(-1);
				break;

			case KEY_RIGHT:
				this->keysPressed += 1;
				ship.startMoving(1);
				break;

			case KEY_START:
				nextState = GS_MENU;
				break;
			}
		}

		if (key_depressed(ks))
		{
			switch (k)
			{
			case KEY_LEFT:
			case KEY_RIGHT:
				this->keysPressed -= 1;
				if (this->keysPressed == 0)
				{
					ship.stopMoving();
				}
				break;
			}
		}

	}
}