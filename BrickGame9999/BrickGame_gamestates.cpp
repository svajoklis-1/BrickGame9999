#include "BrickGame.h"

#include "GSRain.h"
#include "GSMenu.h"
#include "GSSnake.h"
#include "GSArkanoid.h"
#include "GSGameOver.h"

void BrickGame::handleNextGameState(GameStates nextState)
{
	delete gameState;

	switch (nextState)
	{
	case GS_MENU:
		gameState = new GSMenu(*device);
		currentState = GS_MENU;
		break;

	case GS_RAIN:
		gameState = new GSRain(*device);
		currentState = GS_RAIN;
		break;

	case GS_SNAKE:
		gameState = new GSSnake(*device, GSSNAKE_NORMAL);
		currentState = GS_SNAKE;
		break;

	case GS_SNAKEINF:
		gameState = new GSSnake(*device, GSSNAKE_INFINITE);
		currentState = GS_SNAKEINF;
		break;

	case GS_ARKANOID:
		gameState = new GSArkanoid(*device, GSARKANOID_NORMAL);
		currentState = GS_ARKANOID;
		break;

	case GS_GAMEOVER:
		gameState = new GSGameOver(*device, GS_MENU);
		currentState = GS_GAMEOVER;
		break;

	case GS_GAMEOVER_TOCURRENT:
		gameState = new GSGameOver(*device, currentState);
		currentState = GS_GAMEOVER_TOCURRENT;
		break;

	default:
		gameState = new GSMenu(*device);
		break;
	}
}