#include <iostream>
#include <Card.h>
#include <time.h>
#include <Scoring.h>

int numRows = 4;
int numColumns = 4;

Card Cards[16];
int CardNum = 0;
int asciiValues[16];
Card NullCard = Card{ 0,0,0,0,0,0 };

int chosenRow;
int chosenColumn;

Scoring ScoreController;

void SetupCards()
{
    int nextSymbol = 0;
    int ASCIIBase = 43;
    for (int i = 0; i < 16; i++)
    {
        if (nextSymbol < 2)
        {
            Cards[i].frontCard = ASCIIBase;
            nextSymbol++;
        }
        else
        {
            ASCIIBase++;
            if (ASCIIBase == 48)
            {
                ASCIIBase += 10;
            }
            Cards[i].frontCard = ASCIIBase;
            nextSymbol = 1;
        }
    }
}

void SetupAscii()
{
    for (int i = 0; i < 16; i++)
    {
        asciiValues[i] = 0;
    }
}

bool CheckIfCardHasAlreadyBeenAdded(Card card, int ascii[16])
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

void CreateCard(int row, int column)
{
    int r = rand() % 15 + 0;
    if (CardNum <= 0)
    {
        std::cout << " " << Cards[r].backCard;
        asciiValues[CardNum] = Cards[r].frontCard;
        Cards[r].cardsInColumnNum = column;
        Cards[r].cardsInRowNum = row;
        CardNum++;
    }
    else
    {
        while (CheckIfCardHasAlreadyBeenAdded(Cards[r], asciiValues))
        {
            r = rand() % 16;
        }
        std::cout << " " << Cards[r].backCard;
        asciiValues[CardNum] = Cards[r].frontCard;
        Cards[r].cardsInColumnNum = column;
        Cards[r].cardsInRowNum = row;
        CardNum++;
    }
}

void SetUpBoard()
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
                    std::cout << " ~";
                }
            }
            else
            {
                std::cout << " ~";
            }

        }
        std::cout << std::endl;
    }
}

void CheckCardToUpdate(int row, int column)
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
void UpdateBoard()
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
                    std::cout << " ~";
                }
            }
            else
            {
                std::cout << " ~";
            }

        }
        std::cout << std::endl;
    }
}



void FlipCard(int row, int column)
{
    for (int i = 0; i < 16; i++)
    {
        if ((Cards[i].cardsInRowNum == row) && (Cards[i].cardsInColumnNum == column))
        {
            Cards[i].hasBeenFlipped = true;
        }
    }
}

Card* UpdateFlippedCard(int row, int column)
{
    bool isCard = false;
    int cardToSend = 0;
    for (int i = 0; i < 16; i++)
    {
        if ((Cards[i].cardsInRowNum == row) && (Cards[i].cardsInColumnNum == column))
        {
            isCard = true;
            cardToSend = i;
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


void CompareCards(Card &card1, Card &card2)
{
    if ((card1.frontCard != NullCard.frontCard) || (card2.frontCard != NullCard.frontCard))
    {
        if (card1.frontCard == card2.frontCard)
        {
            card1.totalFound = true;
            card2.totalFound = true;
            std::cout << "Found a Match!" << std::endl;
            ScoreController.numOfMatchesFound += 1;
        }
        else
        {
            card1.hasBeenFlipped = false;
            card2.hasBeenFlipped = false;
            std::cout << "Not a Match." << std::endl;
        }
    }
}

void CheckIfGameEnds()
{
    if (ScoreController.numOfMatchesFound >= 8)
    {
        ScoreController.isGameOver = true;
    }
}

void PlayGame()
{
    Card* Card1;
    Card* Card2;
    SetupCards();
    SetUpBoard();
    do
    {
        std::cout << "Choose a card to flip: " << std::endl;
        std::cout << "Please choose a row (don't ignore the rows with ~): ";
        std::cin >> chosenRow;
        std::cout << "Please choose a column (don't ignore the columns with ~): ";
        std::cin >> chosenColumn;
        FlipCard(chosenRow - 1, chosenColumn - 1);
        Card1 = UpdateFlippedCard(chosenRow - 1, chosenColumn - 1);
        UpdateBoard();
        std::cout << "Choose a card to flip: " << std::endl;
        std::cout << "Please choose a row (don't ignore the rows with ~): ";
        std::cin >> chosenRow;
        std::cout << "Please choose a column (don't ignore the columns with ~): ";
        std::cin >> chosenColumn;
        FlipCard(chosenRow - 1, chosenColumn - 1);
        Card2 = UpdateFlippedCard(chosenRow - 1, chosenColumn - 1);
        UpdateBoard();
        CompareCards(*Card1, *Card2);

        UpdateBoard();
        ScoreController.numAttempts++;
        CheckIfGameEnds();
    }

    while (ScoreController.isGameOver == false);



}

int main()
{
    char Confirm;
    srand(time(NULL));
    std::cout << "Welcome to the memory game!" << std::endl;
    std::cout << "Flip the cards to reveal the symbol. When you find two cards with the same symbol, they'll stay unflipped." << std::endl;
    std::cout << "Find all of them and you win!" << std::endl;
    std::cout << "Play Game? (y/n) ";
    std::cin >> Confirm;

    if (Confirm == 'y')
    {
        ScoreController.isGameOver = false;
        PlayGame();
    }
    else if (Confirm == 'n')
    {
        std::cout << "Understood! Hope you play next time!";
        exit(0);
    }

    std::cout << "Congratulations! You win the game!" << std::endl;
    std::cout << "Would you like to play again? (y/n) ";
    std::cin >> Confirm;

    if (Confirm == 'y')
    {
        ScoreController.isGameOver = false;
        PlayGame();
    }
    else if (Confirm == 'n')
    {
        std::cout << "Understood! Thank you for playing.";
        exit(0);
    }

    return 0;
}
