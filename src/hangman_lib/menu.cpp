#include "menu.h"
#include <iostream>
#include <limits>
#include "utilities.h" 

int Menu::showMainMenu() {
    int choice;
    while (true) {
        clearScreen();
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "| Hangman Game              |" << std::endl;
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "| 1. Play                   |" << std::endl;
        std::cout << "| 2. Exit                   |" << std::endl;
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        if (choice < 1 || choice > 2) {
            std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
            continue;
        }

        break;
    }
    return choice;
}

int Menu::showDifficultyMenu() {
    int choice;
    while (true) {
        clearScreen();
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "| Select difficulty:        |" << std::endl;
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "| 1. Easy                   |" << std::endl;
        std::cout << "| 2. Medium                 |" << std::endl;
        std::cout << "| 3. Hard                   |" << std::endl;
        std::cout << "|---------------------------|" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        if (choice < 1 || choice > 3) {
            std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
            continue;
        }

        break;
    }
    return choice;
}
