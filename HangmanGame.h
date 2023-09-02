#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class HangmanGame {
public:
    HangmanGame();
    void Init();
    void ProcessInput(char guess);
    void Draw(sf::RenderWindow& window);
    bool IsGameOver() const {
        return isGameOver;
    }
    void Reset();
    bool IsGameLost() const {
        return attemptsLeft <= 0;
    }
private:
    std::string secretWord;
    std::string guessedWord;
    int attemptsLeft;
    bool isGameOver;
    bool isGameWon;

    sf::Font font;
    sf::Text wordText;
    sf::Text attemptsText;
    sf::Text resultText;

    sf::SoundBuffer correctGuessSoundBuffer;
    sf::SoundBuffer wrongGuessSoundBuffer;
    sf::SoundBuffer winSoundBuffer;
    sf::SoundBuffer loseSoundBuffer;

    sf::Sound correctGuessSound;
    sf::Sound wrongGuessSound;
    sf::Sound winSound;
    sf::Sound loseSound;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    void CheckForWin();
    void UpdateGuessedWord(std::size_t index, char guess);
    void LoadSounds();
};
