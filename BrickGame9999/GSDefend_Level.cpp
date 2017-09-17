#include "GSDefend_Level.hpp"


namespace GSDefend
{
	Level::Level() :
	t(50),
	doAddCell(0, 1)
	{
		this->mapW = logicalScreen.w;
		this->mapH = logicalScreen.h;

		this->map = new bool*[this->mapH];

		for (int i = 0; i < this->mapH; i++)
		{
			this->map[i] = new bool[this->mapW];
		}

		this->reset();
	}

	Level::~Level()
	{
		for (int i = 0; i < this->mapH; i++)
		{
			delete[] this->map[i];
		}

		delete this->map;
	}

	int Level::getWidth() const
	{
		return this->mapW;
	}

	int Level::getHeight() const
	{
		return this->mapH;
	}

	int Level::getCurrentHeight() const
	{
		return this->mapHeight;
	}

	bool Level::getXY(int x, int y) const
	{
		return this->map[y][x];
	}

	bool Level::clearXY(int x, int y)
	{
		bool didClear = this->map[y][x];
		this->map[y][x] = false;

		this->recalculateHeight();

		return didClear;
	}

	void Level::setXY(int x, int y, bool val)
	{
		this->map[y][x] = val;
	}

	void Level::setSpeed(int speed)
	{
		this->t.setLength(50 + (9 - speed) * 7);
	}

	void Level::tick()
	{
		if (this->t.triggered())
		{
			this->generateRow();
			this->t.reset();
		}
		else
		{
			this->t.tick();
		}
	}

	void Level::generateRow()
	{
		bool *droppedRow = this->map[this->mapH - 1];

		for (int i = this->mapH - 1; i >= 1; i--)
		{
			this->map[i] = this->map[i - 1];
		}

		this->map[0] = droppedRow;

		for (int i = 0; i < this->mapW; i++)
		{
			if (this->doAddCell(this->rng) == 0)
			{
				this->map[0][i] = true;
			};
		}

		this->recalculateHeight();
	}

	void Level::recalculateHeight()
	{
		for (int h = this->mapH - 1; h >= 0; h--)
		{
			for (int x = 0; x < this->mapW; x++)
			{
				if (this->getXY(x, h))
				{
					this->mapHeight = h + 1;
					return;
				}
			}
		}
	}

	void Level::reset()
	{
		for (int i = 0; i < this->mapH; i++)
		{
			for (int j = 0; j < this->mapW; j++)
			{
				this->map[i][j] = false;
			}
		}

		this->recalculateHeight();
	}
}