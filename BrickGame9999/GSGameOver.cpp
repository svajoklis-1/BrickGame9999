#include "GSGameOver.h"

GSGameOver::GSGameOver(Device &dev, GameStates nextState) :
stateAfter(nextState)
{
	
}

void GSGameOver::tick(Device &dev)
{
	if (tickCounter >= tickStep)
	{
		tickCounter = 0;
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
		nextState = stateAfter;
	}

	tickCounter++;
}

void GSGameOver::parseEvent(::Device& dev, Key k)
{
	
}