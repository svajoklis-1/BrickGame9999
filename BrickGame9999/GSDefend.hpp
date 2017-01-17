#pragma once

#include "GameState.hpp"
#include "Device.hpp"
#include "GSDefend_Ship.hpp"
#include "GSDefend_Level.hpp"
#include "Explosion.hpp"

namespace GSDefend
{
	class State : public GameState
	{
	public:
		State(Device &dev);

		void tick(Device &dev) override;
		void parseEvent(Device &dev, Key k, KeyState ks) override;
		void render(Device &dev) override;

		int keysPressed = 0;

	private:
		Ship ship;
		Level level;

		bool shipExploded = false;
		Ticker shipExplodedPause;

		Explosion ex;

		
	};
}
