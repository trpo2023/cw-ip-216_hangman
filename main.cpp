#include <SFML/Graphics.hpp>
#include "HangmanGame.h"
#include "MainMenu.h"

bool inGame = true;
bool isGameOverMenuVisible = false;
bool isGameOver = false;

void StartGame(sf::RenderWindow& window, HangmanGame& hangmanGame) {
    hangmanGame.Init();
    isGameOver = false;
    
    while (!hangmanGame.IsGameOver()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    char inputChar = static_cast<char>(event.text.unicode);
                    hangmanGame.ProcessInput(inputChar);
                }
            }
        }

        window.clear(sf::Color::White);
        hangmanGame.Draw(window);

        window.display();
    }
    
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman Game");
    window.setVerticalSyncEnabled(true);

    HangmanGame hangmanGame;
    MainMenu mainMenu(window);

    bool inMainMenu = true;
    bool isGameOver = false; // Перенесли объявление isGameOver сюда

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inMainMenu) {
                mainMenu.HandleInput(event, inMainMenu, inGame);
            }
        }

        window.clear(sf::Color::White);

        if (inMainMenu) {
            window.setActive(false);
            mainMenu.Draw();
            window.setActive(true);
            window.display();
        }
        else if (inGame) {
            if (!isGameOver) { // Проверяем isGameOver здесь
                StartGame(window, hangmanGame);
            }
            else {
                hangmanGame.Draw(window);

                if (!isGameOverMenuVisible) {
                    sf::Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setCharacterSize(40);
                    gameOverText.setFillColor(sf::Color::Black);
                    gameOverText.setString("Game Over! Press Enter to continue or Esc to quit.");

                    window.draw(gameOverText);
                    isGameOverMenuVisible = true;
                }

                // Обработка клавиш для концовки игры
                if (isGameOverMenuVisible) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isGameOver = false;
                        isGameOverMenuVisible = false;
                        hangmanGame.Reset();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window.close();
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}

