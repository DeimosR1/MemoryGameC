#include "Scoring.h"

//Controls whether or not you can play the game.
bool Scoring::RestartSlashFinishGame()
{
	isGameOver = !isGameOver;
	return isGameOver;
}