#pragma once

#include "Global.hpp"
#include "Ticker.hpp"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_01.hpp>

namespace GSDefend
{
	class Level
	{
	public:
		Level();
		~Level();

		int getWidth() const;
		int getHeight() const;
		int getCurrentHeight() const;
		bool getXY(int x, int y) const;
		void clearXY(int x, int y);

		void setSpeed(int speed);

		void tick();

	private:
		void generateRow();
		void setXY(int x, int y, bool val);

		Ticker t;

		bool **map;
		int mapW = 0, mapH = 0;
		int mapHeight = 0;

		boost::random::mt19937 rng;
		boost::random::uniform_int_distribution<> doAddCell;

	};
}
