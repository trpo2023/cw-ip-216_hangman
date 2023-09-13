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

    font.loadFromFile("../resources/arial.ttf");
    backgroundTexture.loadFromFile("../resources/game_background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
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
    correctGuessSoundBuffer.loadFromFile("../resources/correct.wav");
    wrongGuessSoundBuffer.loadFromFile("../resources/wrong.wav");
    winSoundBuffer.loadFromFile("../resources/win.wav");
    loseSoundBuffer.loadFromFile("../resources/lose.wav");

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

HangmanGame::HangmanGame() {};


void HangmanGame::Draw(sf::RenderWindow& window) {
    wordText.setString(guessedWord);
    attemptsText.setString("Attempts left: " + std::to_string(attemptsLeft));

    // Отрисовка фона, слова и оставшихся попыток
    window.draw(backgroundSprite);
    window.draw(wordText);
    window.draw(attemptsText);

    // Отрисовка веревки и горизонтальной палки
    if (attemptsLeft < 6) {
        sf::RectangleShape pole(sf::Vector2f(10.f, 300.f));
        pole.setFillColor(sf::Color::Black);
        pole.setPosition(400.f, 150.f);
        window.draw(pole);

        sf::RectangleShape rope(sf::Vector2f(10.f, 10.f));
        rope.setFillColor(sf::Color::Black);
        rope.setPosition(600.f, 50.f);
        window.draw(rope);

        sf::RectangleShape horizontalBar(sf::Vector2f(150.f, 10.f));
        horizontalBar.setFillColor(sf::Color::Black);
        horizontalBar.setPosition(400.f, 150.f);
        window.draw(horizontalBar);

        sf::RectangleShape ropeBetweenLegs(sf::Vector2f(10.f, 20.f));
        ropeBetweenLegs.setFillColor(sf::Color::Black);
        ropeBetweenLegs.setPosition(400.f, 150.f); // Позиция между веревкой и телом
        window.draw(ropeBetweenLegs);
    }

    // Отрисовка частей повешенного человека
    if (attemptsLeft < 5) {
        sf::CircleShape head(30.f);
        head.setFillColor(sf::Color::White);
        head.setOutlineColor(sf::Color::Black);
        head.setOutlineThickness(2.f);
        head.setPosition(450.f, 170.f);
        window.draw(head);
    }

    if (attemptsLeft < 4) {
        sf::RectangleShape body(sf::Vector2f(10.f, 120.f));
        body.setFillColor(sf::Color::White);
        body.setOutlineColor(sf::Color::Black);
        body.setOutlineThickness(2.f);
        body.setPosition(475.f, 232.f);
        window.draw(body);
    }

    // Отрисовка вертикально поднятой руки
    if (attemptsLeft < 3) {
        sf::RectangleShape leftArm(sf::Vector2f(70.f, 10.f));
        leftArm.setFillColor(sf::Color::White);
        leftArm.setOutlineColor(sf::Color::Black);
        leftArm.setOutlineThickness(2.f);
        leftArm.setPosition(490.f, 250.f); 
        leftArm.setRotation(-45.f); 
        window.draw(leftArm);
    }

    // Отрисовка вертикально поднятой второй руки
    if (attemptsLeft < 2) {
        sf::RectangleShape rightArm(sf::Vector2f(70.f, 10.f));
        rightArm.setFillColor(sf::Color::White);
        rightArm.setOutlineColor(sf::Color::Black);
        rightArm.setOutlineThickness(2.f);
        rightArm.setPosition(422.f, 200.f); 
        rightArm.setRotation(45.f); 
        window.draw(rightArm);
    }

    if (attemptsLeft < 1) {
        sf::RectangleShape leftLeg(sf::Vector2f(70.f, 10.f));
        leftLeg.setFillColor(sf::Color::White);
        leftLeg.setOutlineColor(sf::Color::Black);
        leftLeg.setOutlineThickness(2.f);
        leftLeg.setPosition(490.f, 345.f);
        leftLeg.setRotation(45.f);
        window.draw(leftLeg);

        sf::RectangleShape rightLeg(sf::Vector2f(70.f, 10.f));
        rightLeg.setFillColor(sf::Color::White);
        rightLeg.setOutlineColor(sf::Color::Black);
        rightLeg.setOutlineThickness(2.f);
        rightLeg.setPosition(480.f, 350.f);
        rightLeg.setRotation(135.f);
        window.draw(rightLeg);

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
void HangmanGame::Reset() {
    secretWord = "hangman";
    guessedWord = std::string(secretWord.length(), '_');
    attemptsLeft = 6;
    isGameOver = false;
    isGameWon = false;
}

std::string HangmanGame::GetWrongGuesses() const {
    std::string wrongGuesses;
    for (char guess : secretWord) {
        if (guessedWord.find(guess) == std::string::npos) {
            wrongGuesses += guess;
        }
    }
    return wrongGuesses;
}






