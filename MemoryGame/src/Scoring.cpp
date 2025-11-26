#include "Scoring.h"

bool Scoring::RestartSlashFinishGame()
{
	isGameOver = !isGameOver;
	return isGameOver;
}