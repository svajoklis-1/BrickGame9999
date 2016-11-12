#include "BrickGame.hpp"

#include "GSRain.hpp"
#include "GSMenu.hpp"
#include "GSSnake.hpp"
#include "GSArkanoid.hpp"
#include "GSGameOver.hpp"

void BrickGame::handleNextGameState(GameStates nextState)
{
	delete gameState;

	switch (nextState)
	{
	case GS_MENU:
		l.log(Logger::INFO, "Switching to state (GS_MENU)");
		gameState = new GSMenu(*device);
		currentState = GS_MENU;
		break;

	case GS_RAIN:
		l.log(Logger::INFO, "Switching to state (GS_RAIN)");
		gameState = new GSRain(*device);
		currentState = GS_RAIN;
		break;

	case GS_SNAKE:
		l.log(Logger::INFO, "Switching to state (GS_SNAKE:NORMAL)");
		gameState = new GSSnake::State(*device, GSSnake::VARIANT_NORMAL);
		currentState = GS_SNAKE;
		break;

	case GS_SNAKEINF:
		l.log(Logger::INFO, "Switching to state (GS_SNAKE:INFINITE)");
		gameState = new GSSnake::State(*device, GSSnake::VARIANT_INFINITE);
		currentState = GS_SNAKEINF;
		break;

	case GS_ARKANOID:
		l.log(Logger::INFO, "Switching to state (GS_ARKANOID:NORMAL)");
		gameState = new GSArkanoid(*device, GSARKANOID_NORMAL);
		currentState = GS_ARKANOID;
		break;

	case GS_GAMEOVER:
		l.log(Logger::INFO, "Switching to state (GS_MENU) through GS_GAMEOVER");
		gameState = new GSGameOver(*device, GS_MENU);
		currentState = GS_GAMEOVER;
		break;

	case GS_GAMEOVER_TOCURRENT:
		l.log(Logger::INFO, "Switching to issuing state through GS_GAMEOVER:TOCURRENT");
		gameState = new GSGameOver(*device, currentState);
		currentState = GS_GAMEOVER_TOCURRENT;
		break;

	default:
		l.log(Logger::INFO, "Switching to state (---) defaulting to GS_MENU");
		gameState = new GSMenu(*device);
		break;
	}
}