#pragma once

#include "GameState.hpp"
#include "Ticker.hpp"

namespace GSRain
{
	class State : public GameState
	{
	public:
		State(Device &dev);
		void tick(Device &dev) override;
		void parseEvent(Device &dev, Key k, KeyState state) override;
		void render(Device &dev) override;

	private:

		int numDrops = 10;
		bool drops[10 * 20];

		int ticks = 0;
		int rainTicks = 0;

		int dfrequency = 0;
		int frequency = 5;
		int direction = 1;

		void rainDown();
		void rainFromLeft();
		void rainFromRight();

		void onInputTick();

		Ticker inputTick;
	};
}
