#pragma once
class Scoring
{
	public:
		int numAttempts = 0;
		int numOfMatchesFound = 0;
		bool isGameOver = false;

		bool RestartSlashFinishGame();

};

