#include "GSGameOver.h"

GSGameOver::GSGameOver(Device &/*dev*/, GameStates nextState) :
stateAfter(nextState),
lineTicker(3)
{
	
}

GSGameOver::~GSGameOver()
{
}

void GSGameOver::tick(Device &dev)
{
	switch (transitionState)
	{
	case 0:
		tickCurtain(dev);
		break;
	case 1:
		nextState = stateAfter;
		break;
	}
}

void GSGameOver::tickCurtain(Device &dev)
{
	if (lineTicker.triggered())
	{
		lineTicker.reset();
		lineState++;
	}

	if (lineState <= 20)
	{
		dev.screen.mainArray.fillLines(0, lineState);
	}
	else if (lineState <= 40)
	{
		dev.screen.mainArray.clear();
		dev.screen.mainArray.fillLines(lineState - 20, 20);
	}
	else
	{
		transitionState++;
	}

	lineTicker.tick();
}

void GSGameOver::parseEvent(Device& /*dev*/, Key /*k*/, KeyState /*state*/)
{
	
}