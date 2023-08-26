#include "HangmanGame.h"


void HangmanGame::UpdateGuessedWord(std::size_t index, char guess) {
    guessedWord[index] = guess;
}

void HangmanGame::Init() {
    secretWord = "hangman";
    guessedWord = std::string(secretWord.length(), '_');
    attemptsLeft = 6;
    isGameOver = false;
    isGameWon = false;

    font.loadFromFile("arial.ttf");

    wordText.setFont(font);
    wordText.setCharacterSize(40);
    wordText.setFillColor(sf::Color::Black);
    wordText.setPosition(100, 300);

    attemptsText.setFont(font);
    attemptsText.setCharacterSize(30);
    attemptsText.setFillColor(sf::Color::Black);
    attemptsText.setPosition(100, 100);

    resultText.setFont(font);
    resultText.setCharacterSize(60);
    resultText.setPosition(100, 450);

    LoadSounds();
}

void HangmanGame::LoadSounds() {
    correctGuessSoundBuffer.loadFromFile("correct.wav");
    wrongGuessSoundBuffer.loadFromFile("wrong.wav");
    winSoundBuffer.loadFromFile("win.wav");
    loseSoundBuffer.loadFromFile("lose.wav");

    correctGuessSound.setBuffer(correctGuessSoundBuffer);
    wrongGuessSound.setBuffer(wrongGuessSoundBuffer);
    winSound.setBuffer(winSoundBuffer);
    loseSound.setBuffer(loseSoundBuffer);
}

void HangmanGame::ProcessInput(char guess) {
    bool isGuessCorrect = false;

    if (!isGameOver && !isGameWon) {
        for (std::size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == guess) {
                isGuessCorrect = true;
                UpdateGuessedWord(i, guess);
            }
        }

        if (!isGuessCorrect) {
            attemptsLeft--;
            wrongGuessSound.play();
        }
        else {
            correctGuessSound.play();
        }

        CheckForWin();
    }
}

void HangmanGame::Draw(sf::RenderWindow& window) {
    wordText.setString(guessedWord);
    attemptsText.setString("Attempts left: " + std::to_string(attemptsLeft));

    window.draw(wordText);
    window.draw(attemptsText);

    if (isGameOver) {
        resultText.setString(isGameWon ? "You win!" : "You lose!");
        window.draw(resultText);
    }
}

void HangmanGame::CheckForWin() {
    if (guessedWord == secretWord) {
        isGameOver = true;
        isGameWon = true;
        winSound.play();
    }
    else if (attemptsLeft <= 0) {
        isGameOver = true;
        loseSound.play();
    }
}
