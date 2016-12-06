#pragma once

#include "GameState.hpp"
#include "Ticker.hpp"

using namespace std;

namespace GSGameOver
{
	class State : public GameState
	{
	public:
		State(Device &dev, GameStates nextState);
		~State();
		void tick(Device &dev) override;
		void parseEvent(Device &dev, Key k, KeyState state) override;
		void render(Device &dev) override {};

	private:
		Ticker lineTicker;
		int lineState = 0;

		void tickCurtain(Device &dev);
		void tickExplosion(Device &dev) { };
		int transitionState = 0;

		GameStates stateAfter;
	};
}
