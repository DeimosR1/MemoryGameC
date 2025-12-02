#pragma once
#include <Card.h>
#include "Scoring.h"

class GameSetup
{
    private:
        Scoring ScoreController;

    public:
        int numRows = 4;
        int numColumns = 4;

        Card Cards[16];
        int CardNum = 0;
        int asciiValues[16];
        Card NullCard = Card{ 0,0,0,0,0,0 };

        int chosenRow;
        int chosenColumn;

        Scoring& GetScoreControllerObject() { return ScoreController; }

        void SetupCards();

        void SetupAscii();

        bool CheckIfCardHasAlreadyBeenAdded(Card card, int ascii[16]);

        void CreateCard(int row, int column);

        void SetUpBoard();

        void CheckCardToUpdate(int row, int column);

        void UpdateBoard();

        void FlipCard(int row, int column);

        Card* UpdateFlippedCard(int row, int column);


        void CompareCards(Card& card1, Card& card2);

        void CheckIfGameEnds();

        int ConvertRowColumn(int playerInput);

        void PlayGame();

        void ShuffleCards();

};

