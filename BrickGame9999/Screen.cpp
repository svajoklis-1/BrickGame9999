#include "Screen.h"

Screen::Screen() :
score(6),
highScore(6),
level(1),
speed(1),
mainArray(10, 20),
hintArray(4, 4)
{
	clear();
}

Screen::~Screen()
{

}

void Screen::clear()
{
	score.clear();
	highScore.clear();
	level.clear();
	speed.clear();

	mainArray.clear();
	hintArray.clear();
}