#include "GSSnake_snake.hpp"

#include "Global.hpp"
#include "Ticker.hpp"

namespace GSSnake
{
	Snake::Snake(Device &dev) :
		snakeHeadBlinkTicker(3)
	{
		reset(dev);
	}

	void Snake::reset(Device &dev)
	{
		length = 3;
		snakeHeadX = logicalScreen.w / 2;
		snakeHeadY = logicalScreen.h / 2;

		segments[0] = { snakeHeadX, snakeHeadY };
		segments[1] = { snakeHeadX - 1, snakeHeadY };
		segments[2] = { snakeHeadX - 2, snakeHeadY };

		snakeHeadBlinkTicker.reset();

		dir = RIGHT;

		setSpeedBySpeed(dev.getSpeed());
	}

	int Snake::setSpeedBySpeed(int newSpeed)
	{
		speed = 15 - newSpeed;
		return speed;
	}

	void Snake::parseEvent(Key k, KeyState state)
	{
		if (key_pressed(state))
		{
			if (!didTurn)
			{
				int old_dir = dir;
				switch (k)
				{
				case KEY_ACTION: break;

				case KEY_LEFT:
					if (dir != RIGHT)
						dir = LEFT;
					break;

				case KEY_RIGHT:
					if (dir != LEFT)
						dir = RIGHT;
					break;

				case KEY_UP:
					if (dir != DOWN)
						dir = UP;
					break;

				case KEY_DOWN:
					if (dir != UP)
						dir = DOWN;
					break;

				default: break;
				}

				if (old_dir != dir)
				{
					didTurn = true;
				}
			}

			if (k == KEY_ACTION)
			{
				speeding = true;
			}
		}

		if (key_released(state))
		{
			if (k == KEY_ACTION)
			{
				speeding = false;
			}
		}
			
	}

	void Snake::tick(Device &dev)
	{
		// reset turn protection
		didTurn = false;

		// remove last segment
		for (int i = length; i >= 0; i--)
		{
			segments[i] = segments[i - 1];
		}

		// move snake
		switch (dir)
		{
		case LEFT:
			snakeHeadX--;
			if (snakeHeadX < 0)
				snakeHeadX = logicalScreen.w - 1;
			break;

		case UP:
			snakeHeadY--;
			if (snakeHeadY < 0)
				snakeHeadY = logicalScreen.h - 1;
			break;

		case RIGHT:
			snakeHeadX++;
			if (snakeHeadX >= logicalScreen.w)
				snakeHeadX = 0;
			break;

		case DOWN:
			snakeHeadY++;
			if (snakeHeadY >= logicalScreen.h)
				snakeHeadY = 0;
			break;

		default: break;
		}

		segments[0] = { snakeHeadX, snakeHeadY };

	}

	coord Snake::getHead()
	{
		return segments[0];
	}

	bool Snake::doesCollide(coord c)
	{
		for (int i = 0; i < length; i++)
		{
			if (c == segments[i])
			{
				return true;
			}
		}

		return false;
	}

	void Snake::render(Device &dev)
	{
		snakeHeadBlinkTicker.tick();
		// blink head
		if (snakeHeadBlinkTicker.triggered())
		{
			snakeHeadBlinkTicker.reset();
		}

		for (int i = 0; i < length; i++)
		{
			if (i != 0 || snakeHeadBlinkTicker.getState(2) == true || speeding)
				dev.screen.mainArray.setPixel(segments[i], PXARRAY_ON);
		}
		
	}

	coord Snake::getSegment(int index)
	{
		if (index < 0 || index >= length)
		{
			l.log(Logger::ASSERT, "Attempting to access snake segment beyond its length");
			return { 0, 0 };
		}

		return segments[index];
	}

}