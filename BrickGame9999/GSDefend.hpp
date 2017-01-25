#pragma once

#include "GameState.hpp"
#include "Device.hpp"
#include "GSDefend_Ship.hpp"
#include "GSDefend_Level.hpp"
#include "Explosion.hpp"
#include "GSDefend_Bullet.hpp"
#include <list>

namespace GSDefend
{
	class State : public GameState
	{
	public:
		State(Device &dev);

		void tick(Device &dev) override;
		void parseEvent(Device &dev, Key k, KeyState ks) override;
		void render(Device &dev) override;

	private:
		Ship ship;
		Level level;
		list<Bullet> bullets;

		void reset(Device &dev);

		bool isShooting = false;
		Ticker shootT;
		bool shipExploded = false;
		Ticker shipExplodedPause;

		int movementKeysPressed = 0;
		int blocksToClear = 50;
		int blocksCleared = 0;

		Explosion ex;

		
	};
}
