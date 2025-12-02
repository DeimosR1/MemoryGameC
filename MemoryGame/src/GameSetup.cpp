#include <iostream>
#include "GameSetup.h"
#include <Card.h>
#include <time.h>
#include <algorithm>

    void GameSetup::SetupCards()
    {
        int nextSymbol = 0;
        int ASCIIBase = 33;
        for (int i = 0; i < 16; i++)
        {
            //Setting up the front Symbols
            if (nextSymbol < 2)
            {
                Cards[i].frontCard = ASCIIBase;
                nextSymbol++;
            }
            else
            {
                ASCIIBase++;
                if (ASCIIBase == 35)
                {
                    ASCIIBase += 1;
                }
                Cards[i].frontCard = ASCIIBase;
                nextSymbol = 1;
            }

            //Initializing Values
            Cards[i].hasBeenFlipped = false;
            Cards[i].totalFound = false;
            Cards[i].cardsInRowNum = -1;    // not placed yet
            Cards[i].cardsInColumnNum = -1; // not placed yet
        }
    }

    void GameSetup::SetupAscii()
    {
        for (int i = 0; i < 16; i++)
        {
            asciiValues[i] = 0;
        }
    }

    bool GameSetup::CheckIfCardHasAlreadyBeenAdded(Card card, int ascii[16])
    {
        int repeats = 0;
        for (int i = 0; i < 16; i++)
        {
            if (card.frontCard == ascii[i])
            {
                repeats += 1;
            }
        }

        if (repeats < 2)
        {
            return false;
        }
        else
        {
            return true;
        }

        return true;
    }

    void GameSetup::ShuffleCards()
    {
        for (int i = 0; i < 16; i++)
        {
            int j = rand() % 16;
            std::swap(Cards[i], Cards[j]);
        }
    }


    void GameSetup::CreateCard(int row, int column)
    {
        int r = CardNum;

        std::cout << " " << Cards[r].backCard;
        asciiValues[CardNum] = Cards[r].frontCard;

        Cards[r].cardsInColumnNum = column;
        Cards[r].cardsInRowNum = row;

        CardNum++;
    }

    void GameSetup::SetUpBoard()
    {
        for (int rows = 0; rows < ((numRows * 2) + 1); rows++)
        {
            for (int columns = 0; columns < ((numColumns * 2) + 1); columns++)
            {
                if ((rows % 2) > 0)
                {
                    if ((columns % 2) > 0)
                    {
                        CreateCard(rows, columns);
                    }
                    else
                    {
                        std::cout << " |";
                    }
                }
                else
                {
                    std::cout << " -";
                }

            }
            std::cout << std::endl;
        }
    }

    void GameSetup::CheckCardToUpdate(int row, int column)
    {
        bool notFound = true;
        for (int i = 0; i < 16; i++)
        {
            if (Cards[i].cardsInRowNum == row)
            {
                if (Cards[i].cardsInColumnNum == column)
                {
                    if (Cards[i].hasBeenFlipped)
                    {
                        std::cout << " " << Cards[i].frontCard;
                        notFound = false;
                    }
                    else if (Cards[i].totalFound)
                    {
                        std::cout << " " << Cards[i].frontCard;
                        notFound = false;
                    }
                }
            }
        }

        if (notFound)
        {
            std::cout << " " << Cards[0].backCard;
        }
    }
    void GameSetup::UpdateBoard()
    {

        for (int rows = 0; rows < ((numRows * 2) + 1); rows++)
        {
            for (int columns = 0; columns < ((numColumns * 2) + 1); columns++)
            {
                if ((rows % 2) > 0)
                {
                    if ((columns % 2) > 0)
                    {
                        CheckCardToUpdate(rows, columns);
                    }
                    else
                    {
                        std::cout << " |";
                    }
                }
                else
                {
                    std::cout << " -";
                }

            }
            std::cout << std::endl;
        }
    }



    void GameSetup::FlipCard(int row, int column)
    {
        for (int i = 0; i < 16; i++)
        {
            if ((Cards[i].cardsInRowNum == row) && (Cards[i].cardsInColumnNum == column))
            {
                Cards[i].hasBeenFlipped = true;
            }
        }
    }

    Card* GameSetup::UpdateFlippedCard(int row, int column)
    {
        bool isCard = false;
        int cardToSend = 0;
        for (int i = 0; i < 16; i++)
        {
            if ((Cards[i].cardsInRowNum == row) && (Cards[i].cardsInColumnNum == column))
            {
                isCard = true;
                cardToSend = i;
                break; //stops at the first matching card.
            }
        }

        if (isCard)
        {
            return &Cards[cardToSend];
        }
        else
        {
            return &NullCard;
        }
    }


    void GameSetup::CompareCards(Card& card1, Card& card2)
    {
        if (card1.frontCard == NullCard.frontCard || card2.frontCard == NullCard.frontCard)
        {
            std::cout << "Invalid card selection." << std::endl;
            return;
        }

        if (card1.frontCard == card2.frontCard)
        {
            card1.totalFound = true;
            card2.totalFound = true;
            std::cout << "Found a Match!" << std::endl;
            ScoreController.numOfMatchesFound += 1;
            ScoreController.numAttempts++;
        }

        else
        {
            card1.hasBeenFlipped = false;
            card2.hasBeenFlipped = false;
            std::cout << "Not a Match." << std::endl;
            ScoreController.numAttempts++;
        }
    }

    void GameSetup::CheckIfGameEnds()
    {
        if (ScoreController.numOfMatchesFound >= 8)
        {
            ScoreController.isGameOver = true;
        }
    }

    int GameSetup::ConvertRowColumn(int playerInput)
    {
        if (playerInput < 1 || playerInput > 4)
        {
            return -1;
        }

        return (playerInput * 2)-1; // row becomes 1,3,5,7
    }

    void GameSetup::PlayGame()
    {
        //Clean Start
        CardNum = 0;
        ScoreController.numOfMatchesFound = 0;
        ScoreController.numAttempts = 0;
        ScoreController.isGameOver = false;

        //Reset Cards
        for (int i = 0; i < 16; i++)
        {
            Cards[i].cardsInRowNum = -1;
            Cards[i].cardsInColumnNum = -1;
            Cards[i].hasBeenFlipped = false;
            Cards[i].totalFound = false;
        }

        //Seed RNG and init trackers
        srand(static_cast<unsigned int>(time(nullptr)));
        SetupAscii();

        //Preparing Cards and Board
        Card* Card1;
        Card* Card2;
        SetupCards();
        ShuffleCards();
        SetUpBoard();

        //Reset Null Card
        NullCard = Card{ 0,0,0,0,0,0 };


        do
        {
            std::cout << "Choose a card to flip: " << std::endl;
            std::cout << "Please choose a row (1-4, ignore the rows without #): ";
            std::cin >> chosenRow;
            std::cout << "Please choose a column (1-4, ignore the columns without #): ";
            std::cin >> chosenColumn;

            int newRow = ConvertRowColumn(chosenRow);
            int newCol = ConvertRowColumn(chosenColumn);

            if (newRow == -1 || newCol == -1)
            {
                std::cout << "Invalid Input. Please try again." << std::endl;
                UpdateBoard();
                continue; //This asks again.
            }
            FlipCard(newRow, newCol);
            Card1 = UpdateFlippedCard(newRow, newCol);
            UpdateBoard();
            std::cout << "Choose a card to flip: " << std::endl;
            std::cout << "Please choose a row (don't ignore the rows with ~): ";
            std::cin >> chosenRow;
            std::cout << "Please choose a column (don't ignore the columns with ~): ";
            std::cin >> chosenColumn;

            newRow = ConvertRowColumn(chosenRow);
            newCol = ConvertRowColumn(chosenColumn);

            if (newRow == -1 || newCol == -1)
            {
                std::cout << "Invalid Input. Please try again." << std::endl;
                UpdateBoard();
                continue; //This asks again.
            }
            FlipCard(newRow, newCol);
            Card2 = UpdateFlippedCard(newRow, newCol);
            UpdateBoard();
            CompareCards(*Card1, *Card2);

            UpdateBoard();
            CheckIfGameEnds();
        }

        while (ScoreController.isGameOver == false);

    }


