#pragma once

#include "GameState.hpp"
#include "Ticker.hpp"
#include "Explosion.hpp"

#include "GSArkanoid_Ball.hpp"
#include "GSArkanoid_Paddle.hpp"

namespace GSArkanoid
{
	enum Variant
	{
		VARIANT_NORMAL,
		VARIANT_DOUBLE
	};

	class State : public GameState
	{
	public:
		State(Device &dev, Variant variant);
		void tick(Device& dev) override;
		void parseEvent(Device& dev, Key k, KeyState state) override;
		void render(Device& dev) override;
		~State() override;

		Ball b;
		Paddle p;
		bool slid = false;

		void clearBlock(Device &dev, int location);
		bool isBlockOccupied(Device &deve, int location);

	private:
		Variant currentVariant;

		enum stateSegments
		{
			SEG_PAUSE = 0,
			SEG_GAME,
			SEG_EXPLOSION
		};

		void reset(Device &dev);
		void resetLevel(Device &dev);

		static string currentLevel;
		static int currentCount;

		int stateSegment = 0;

		void tickPause(Device &dev);
		void tickGame(Device &dev);
		void tickExplosion(Device &dev);
		void renderGame(Device &dev);

		void postEvents(Device &device) override;

		int directionKeysPressed = 0;

		int levelCount = 0;

		Ticker pauseTicker;

		Explosion explosion;

		struct level
		{
			string data;
			int count;
		};
		map<int, level> levels;
		void defineLevels();
	};
}
