#pragma once
class Scoring
{
	//Setting up the Scoring Variables that are needed to keep track and control the game.
	public:
		int numAttempts = 0;
		int numOfMatchesFound = 0;
		bool isGameOver = false;

		bool RestartSlashFinishGame();

};

