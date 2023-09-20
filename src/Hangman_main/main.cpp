#include "../hangman_lib/menu.h"
#include "../hangman_lib/hangman.h"
#include <iostream>

int main() {
    while (true) {
        int mainChoice = Menu::showMainMenu();
        if (mainChoice == 1) {
            int difficultyChoice = Menu::showDifficultyMenu();
            std::string difficulty;
            
            switch (difficultyChoice) {
                case 1:
                    difficulty = "easy";
                    break;
                case 2:
                    difficulty = "medium";
                    break;
                case 3:
                    difficulty = "hard";
                    break;
                default:
                    break;
            }

            Hangman game(difficulty);
            game.play();
        } else if (mainChoice == 2) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
    }

    return 0;
}
