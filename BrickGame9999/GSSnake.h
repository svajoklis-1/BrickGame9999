#pragma once

#include "GameState.h"
#include "Ticker.h"
#include "Explosion.h"
#include "GSSnake_snake.h"

using namespace std;

namespace GSSnake
{
	enum Variant
	{
		VARIANT_NORMAL,
		VARIANT_INFINITE
	};

	class State : public GameState
	{
	public:
		State(Device &dev, Variant variant);
		~State();
		void tick(Device &dev) override;
		void parseEvent(Device &dev, Key k, KeyState state) override;
		void render(Device &dev) override;

	private:

		Variant currentVariant;
		char highScoreLetter;

		Ticker snakeTicker;
		Snake snake;

		int snakeLengthRequired;

		coord food;
		void genFood(int level);

		int gameTick = 0;
		const int gameStartPauseDurationTicks = 60;
		const int explosionDurationTicks = 60;

		void reset(Device &dev);

		map<int, string> levels;
		int levelCount;
		void defineLevels();

		Ticker foodTicker;

		int stateSegment = 0;

		void renderSnake(Device &dev);

		void tickSnake(Device &dev);
		void tickPause(Device &dev);
		void tickExplosion(Device &dev);

		Explosion explosion;
	};
}
