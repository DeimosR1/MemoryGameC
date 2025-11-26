#pragma once
class Card
{
	public:
		char backCard = '|';
		char frontCard = '~';
		bool totalFound = false;
		bool hasBeenFlipped = false;
		int cardsInRowNum = 0;
		int cardsInColumnNum = 0;

		void SetupCard(char front);

};

