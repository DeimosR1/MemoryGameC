#include <iostream>
#include "GameSetup.h"
#include "Scoring.h"
#include <time.h>

GameSetup GameController;

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
        GameController.GetScoreControllerObject().isGameOver = false;
        GameController.PlayGame();
    }
    else if (Confirm == 'n')
    {
        std::cout << "Understood! Hope you play next time!";
        exit(0);
    }

    std::cout << "Congratulations! You win the game!" << std::endl;
    std::cout << "Your total move count was: " << GameController.GetScoreControllerObject().numAttempts << std::endl;
    std::cout << "Would you like to play again? (y/n) ";
    std::cin >> Confirm;

    if (Confirm == 'y')
    {
        GameController.GetScoreControllerObject().isGameOver = false;
        GameController.PlayGame();
    }
    else if (Confirm == 'n')
    {
        std::cout << "Understood! Thank you for playing.";
        exit(0);
    }

    return 0;
}
