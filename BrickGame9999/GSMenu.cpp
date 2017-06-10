#include "GSMenu.hpp"
#include "GSMenu_LetterRenderer.hpp"

namespace GSMenu
{
	int State::currentL = 0;

	State::State(Device &dev) :
		letterTurnDelay(60),
		letterTurn(10),
		animTicker(60)
	{
		defineGraphics();

		dev.screen.score.dash();

		dev.screen.hintArray.clear();

		dev.inGame = false;
	}

	void State::resetAnim()
	{
		animFrame = 0;
		animTicker.reset();
	}

	void State::parseEvent(Device &dev, Key k, KeyState state)
	{
		if (state == STATE_DOWN)
		{
			int currentSpeed = 0;
			int currentLevel = 0;
			switch (k)
			{
			case KEY_LEFT:
				dev.speaker.playSound(SND_BLIP);
				stage--;
				if (stage < 0)
					stage = 99;
				break;

			case KEY_RIGHT:
				dev.speaker.playSound(SND_BLIP);
				stage++;
				if (stage > 99)
					stage = 0;
				break;

			case KEY_UP:
				dev.speaker.playSound(SND_BLIP);
				currentSpeed = dev.getSpeed();
				if (currentSpeed == 9)
					dev.setSpeed(0);
				else
					dev.setSpeed(currentSpeed + 1);
				break;

			case KEY_DOWN:
				dev.speaker.playSound(SND_BLIP);
				currentLevel = dev.getLevel();
				if (currentLevel == 9)
					dev.setLevel(0);
				else
					dev.setLevel(currentLevel + 1);
				break;

			case KEY_ACTION:
				currentL += 1;
				if (currentL >= letterCount)
					currentL = 0;

				resetAnim();
				letterTurnDelay.reset();
				letterTurnDelay.resetPeriodCount();
				letterTurn.reset();
				letterTurn.resetPeriodCount();
				break;

			case KEY_START: break;
			case KEY_RESET: break;
			case KEY_TOTAL: break;

			default: break;
			}
		}
		else
		{

		}

	}

	GameStates State::getSelectedState()
	{
		switch (currentL)
		{
		case R:
			return GS_RAIN;
		case A:
			return GS_SNAKE;
		case B:
			return GS_SNAKEINF;
		case C:
			return GS_ARKANOID;
		case D:
			return GS_DEFEND;
		default:
			return GS_NONE;
		}
	}

	void State::tick(Device &/*dev*/)
	{
		animTicker.tick();
		if (animTicker.triggered())
		{
			animTicker.reset();

			animFrame++;
			if (animFrame >= 4)
				animFrame = 0;
		}

		letterTurnDelay.tick();
		if (letterTurnDelay.triggered())
		{
			letterTurn.tick();
			if (letterTurn.triggered())
			{
				letterTurn.reset();
				if (letterTurn.getPeriodCount() == 8)
				{
					letterTurn.resetPeriodCount();
					letterTurnDelay.reset();
				}
			}
		}

	}

	void State::drawNumber(Device& dev)
	{
		int drawX = numberX + numberW + 1;

		int tens = stage / 10;
		int singles = stage % 10;

		dev.screen.mainArray.copyString(drawX, numberY, numbers[singles], numberW, numberH);

		drawX = numberX;

		dev.screen.mainArray.copyString(drawX, numberY, numbers[tens], numberW, numberH);
	}

	void State::render(Device &dev)
	{
		dev.screen.mainArray.clear();

		dev.screen.speed.setNumber(dev.getSpeed());
		dev.screen.level.setNumber(dev.getLevel());

		dev.screen.highScore.setNumber(dev.highScore[letterChars[currentL]]);

		LetterRenderer::renderHorizontallyRotatedLetter(dev, letters[currentL], letterW, letterH, letterX, letterY, letterTurn.getPeriodCount() % 8);

		drawNumber(dev);

		renderAnim(dev);
	}

	void State::renderAnim(Device &dev)
	{
		if (anims.find(currentL) != anims.end())
			dev.screen.mainArray.copyString(1, 6, anims[currentL][animFrame], animW, animH);
	}


	State::~State()
	{
	}


}
