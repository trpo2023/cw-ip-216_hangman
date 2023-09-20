#include "hangman.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include "utilities.h" 

bool Hangman::isWordGuessed() const {
    return secretWord == guessedWord;
}
bool Hangman::isGameWon() const {
    return isWordGuessed();
}

void Hangman::drawHangman() {
    // Отображение виселицы в текстовом режиме в зависимости от количества оставшихся попыток
    std::cout << "Attempts left: " << attempts << std::endl;
    
    // Отступы перед виселицей
    std::cout << "   ____" << std::endl;
    std::cout << "   |  |" << std::endl;

    if (attempts < 5) {
        std::cout << "   |  O" << std::endl;
    }
    if (attempts < 4) {
        std::cout << "   |";
        if (attempts < 3) {
            std::cout << " /|\\";
        }
        std::cout << std::endl;
    }
    if (attempts < 2) {
        std::cout << "   |";
        if (attempts < 1) {
            std::cout << " / \\";
        }
        std::cout << std::endl;
    }
    std::cout << "______|" << std::endl;
}

void Hangman::drawKeyboard() {
    // Отображение клавиатуры в текстовом режиме с учетом угаданных букв
    std::cout << "Keyboard:" << std::endl;
    for (char c = 'A'; c <= 'Z'; ++c) {
        char lowerC = std::tolower(c); // Преобразование буквы в нижний регистр

        if (std::find(correctGuesses.begin(), correctGuesses.end(), c) != correctGuesses.end() ||
            std::find(correctGuesses.begin(), correctGuesses.end(), lowerC) != correctGuesses.end() ||
            std::find(incorrectGuesses.begin(), incorrectGuesses.end(), c) != incorrectGuesses.end() ||
            std::find(incorrectGuesses.begin(), incorrectGuesses.end(), lowerC) != incorrectGuesses.end()) {
            // Буква уже угадана, не отображаем ее
            std::cout << "  ";
        } else {
            std::cout << c << ' ';
        }

        if (c == 'H' || c == 'N') {
            std::cout << std::endl; // Переход на новую строку для клавиш "H" и "N"
        }
    }
    std::cout << std::endl;
}

void Hangman::displayGuessedWord() {
    std::cout << "Word: " << guessedWord << std::endl;
}

void Hangman::updateGuessedWord(char guess) {
    bool guessed = false;
    bool alreadyGuessed = false;

    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == guess || secretWord[i] == std::tolower(guess)) {
            if (guessedWord[i] == '_') {
                guessedWord[i] = secretWord[i];
                guessed = true;
            } else {
                alreadyGuessed = true;
            }
        }
    }

    if (!guessed) {
        if (!alreadyGuessed) {
            incorrectGuesses.push_back(guess);
            attempts--;
        }
    }
}

void Hangman::play() {
    while (attempts > 0) {
        std::cout << std::string(50, '\n');
        clearScreen();
        drawHangman();
        drawKeyboard();
        displayGuessedWord();

        std::cout << "Enter a letter: ";
        char guess;
        std::cin >> guess;

        if ((guess >= 'A' && guess <= 'Z') || (guess >= 'a' && guess <= 'z')) {
            if (std::find(correctGuesses.begin(), correctGuesses.end(), guess) != correctGuesses.end() ||
                std::find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end()) {
                continue; // Проверка, была ли буква уже угадана
            }

            updateGuessedWord(guess); // Обновляем угаданные буквы в слове

            if (secretWord.find(guess) != std::string::npos || secretWord.find(std::tolower(guess)) != std::string::npos) {
                correctGuesses.push_back(guess);
            }

            if (isWordGuessed()) {
                std::cout << "Congratulations! You guessed the word: " << secretWord << std::endl;
                break;
            }
        }
    }

    if (attempts == 0) {
        std::cout << "Sorry, you ran out of attempts. The word was: " << secretWord << std::endl;
    }
}

bool Hangman::isGameOver() const {
    return attempts <= 0 || isWordGuessed();
}


Hangman::Hangman(const std::string& difficulty) {
    // Инициализация случайного генератора
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (difficulty == "easy") {
        // Здесь можно добавить список слов для угадывания для легкого уровня сложности
        std::vector<std::string> easyWords = {"apple", "banana", "cherry"};
        secretWord = easyWords[std::rand() % easyWords.size()];
    } else if (difficulty == "medium") {
        // Здесь можно добавить список слов для угадывания для среднего уровня сложности
        std::vector<std::string> mediumWords = {"elephant", "giraffe", "kangaroo"};
        secretWord = mediumWords[std::rand() % mediumWords.size()];
    } else if (difficulty == "hard") {
        // Здесь можно добавить список слов для угадывания для сложного уровня сложности
        std::vector<std::string> hardWords = {"javascript", "python", "cplusplus"};
        secretWord = hardWords[std::rand() % hardWords.size()];
    }

    guessedWord = std::string(secretWord.length(), '_');
    attempts = 6;
}


std::string Hangman::getCorrectGuessesAsString() {
    std::string result;
    for (char guess : correctGuesses) {
        result += guess;
        result += ", ";
    }
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

std::string Hangman::getGuessedWord() {
    return guessedWord;
}

int Hangman::getRemainingAttempts() const {
    return attempts;
}

