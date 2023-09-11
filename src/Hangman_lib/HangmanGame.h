#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


class HangmanGame {
public:
    HangmanGame();
    void Init();
    void ProcessInput(char guess);
    void Draw(sf::RenderWindow& window);
    void Reset();
    bool IsGameWon() const {
        return guessedWord == secretWord;
    }
    std::string GetWrongGuesses() const;
    bool IsGameOver() const {
        return attemptsLeft == 0 || IsGameWon();
    }
    std::string GetSecretWord() const {
        return secretWord;
    }
    enum class GameState {
        Playing,
        Win,
        Lose
    };
    std::string GetGuessedWord() const {
        return guessedWord;
    }

    int GetAttemptsLeft() const {
        return attemptsLeft;
    }
    GameState GetGameState() const {
        return gameState;
    }
private:
    std::string targetWord;
    std::string secretWord;
    std::string guessedWord;
    int attemptsLeft;
    bool isGameOver;
    bool isGameWon;
    GameState gameState = GameState::Playing;

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
