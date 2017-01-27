#include "GSDefend.hpp"

namespace GSDefend
{

	State::State(Device &dev) :
	shootT(7)
	{
		this->shipExploded = false;
		this->shipExplodedPause.setLength(60);
		if (!dev.inGame)
		{
			dev.lives = 3;
		}

		dev.screen.score.setLink(&dev.score);
		dev.highScoreLetter = 'D';
		dev.screen.highScore.setLink(&dev.highScore[dev.highScoreLetter]);

		this->level.setSpeed(dev.getSpeed());
		dev.screen.speed.setLink(&dev.getSpeedRef());

		this->reset(dev);

		dev.inGame = true;
	}

	void State::tick(Device &dev)
	{
		if (this->shipExploded)
		{
			this->shipExplodedPause.tick();
			if (this->shipExplodedPause.triggered())
			{
				if (dev.lives == 0)
				{
					nextState = GS_GAMEOVER;
				}
				else
				{
					nextState = GS_GAMEOVER_TOCURRENT;
				}
			}

			return;
		}

		this->level.tick();
		this->ship.tick();

		if (this->level.getCurrentHeight() >= logicalScreen.h)
		{
			ex.setCoord({ this->ship.getX(), logicalScreen.h - 1 });
			dev.speaker.playSound(SND_EXPLODE);
			dev.lives -= 1;
			this->shipExploded = true;
		}

		if (this->isShooting)
		{
			this->shootT.tick();
			if (this->shootT.triggered())
			{
				this->shootT.reset();
				bullets.push_back(Bullet(DIR_UP, this->ship.getX(), logicalScreen.h - 2));
			}
		}

		point bullet_loc;
		auto bullet_it = bullets.begin();
		bool levelEnd = false;
		while (!levelEnd && bullet_it != bullets.end())
		{
			bullet_loc = bullet_it->getPosition();

			if (bullet_loc.x < 0 || bullet_loc.x >= logicalScreen.w || bullet_loc.y < 0 || bullet_loc.y >= logicalScreen.h)
			{
				bullet_it = bullets.erase(bullet_it);
				continue;
			}

			if (level.clearXY(bullet_loc.x, bullet_loc.y))
			{
				dev.speaker.playSound(SND_BLIP);
				dev.increaseScore(10);
				bullet_it = bullets.erase(bullet_it);
				this->blocksCleared += 1;

				if (this->blocksCleared >= this->blocksToClear)
				{
					levelEnd = true;
					dev.increaseScore(50 * dev.getSpeed());
					dev.setSpeed(dev.getSpeed() + 1);
					this->reset(dev);
				}

				continue;
			}
			bullet_it->tick();

			++bullet_it;
		}
	}

	void State::render(Device &dev)
	{
		Screen &s = dev.screen;
		s.clear();

		dev.screen.score.setLinked();
		dev.screen.highScore.setLinked();
		dev.screen.hintArray.setCount(dev.lives);
		dev.screen.level.dash();
		dev.screen.speed.setLinked();

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

		point bullet_loc;
		auto bullet_it = bullets.begin();
		while (bullet_it != bullets.end())
		{
			bullet_loc = bullet_it->getPosition();
			s.mainArray.setPixel(bullet_loc.x, bullet_loc.y, PXARRAY_ON);
			++bullet_it;
		}
	}

	void State::parseEvent(Device &dev, Key k, KeyState ks)
	{
		if (key_pressed(ks))
		{
			switch (k)
			{
			case KEY_LEFT:
				this->movementKeysPressed += 1;
				ship.startMoving(-1);
				break;

			case KEY_RIGHT:
				this->movementKeysPressed += 1;
				ship.startMoving(1);
				break;

			case KEY_START:
				nextState = GS_MENU;
				break;

			case KEY_ACTION:
				this->isShooting = true;
				this->shootT.forceTrigger();
				break;
			}
		}

		if (key_released(ks))
		{
			switch (k)
			{
			case KEY_LEFT:
			case KEY_RIGHT:
				this->movementKeysPressed -= 1;
				if (this->movementKeysPressed == 0)
				{
					ship.stopMoving();
				}
				break;

			case KEY_ACTION:
				this->isShooting = false;
				this->shootT.reset();
				break;
			}
		}

	}

	void State::reset(Device &dev)
	{
		this->blocksToClear = 50 + 10 * dev.getSpeed();
		this->blocksCleared = 0;
		this->level.reset();
		this->ship.reset();
		this->bullets.clear();
	}
}