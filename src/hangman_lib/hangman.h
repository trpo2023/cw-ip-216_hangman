#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>

class Hangman {
public:
    Hangman();
    void play();
    Hangman(const std::string& difficulty);
    std::string getCorrectGuessesAsString();
    std::string getGuessedWord();
    void updateGuessedWord(char guess);
    bool isWordGuessed() const;
    bool isGameWon() const;
    int getRemainingAttempts() const;
    bool isGameOver() const;
    void setInitialWord(const std::string& word) {
        secretWord = word;
        guessedWord = std::string(secretWord.length(), '_');
        attempts = 6;
    }

private:
    std::string secretWord;
    std::string guessedWord;
    int attempts;
    std::vector<char> incorrectGuesses;
    std::vector<char> correctGuesses;
    std::vector<std::string> easyWords;
    std::vector<std::string> mediumWords;
    std::vector<std::string> hardWords;
    void drawHangman();
    void drawKeyboard();
    void displayGuessedWord();
};

#endif
