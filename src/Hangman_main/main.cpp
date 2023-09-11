#include <SFML/Graphics.hpp>
#include "../Hangman_lib/HangmanGame.h"
#include "../Hangman_lib/MainMenu.h"
#include <iostream>

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

        if (hangmanGame.IsGameWon()) {
            std::cout << "You win!" << std::endl;
            isGameOver = true;
        }
    }

    if (!hangmanGame.IsGameWon()) {
        std::cout << "You lose!" << std::endl;
        isGameOver = true;
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Hangman Game");
    window.setVerticalSyncEnabled(true);

    HangmanGame hangmanGame;
    MainMenu mainMenu(window);
    MainMenu menu(window);
    bool inMainMenu = true;
    bool inGame = false;

    sf::Font font;
    if (!font.loadFromFile("../Assetst/arial.ttf")) {
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

        isGameOverMenuVisible = false;

        window.clear(sf::Color::White);

        if (inMainMenu) {
            window.setActive(false);
            mainMenu.Draw();
            window.setActive(true);
            window.display();
        }
        else if (inGame) {
            if (!isGameOver) {
                StartGame(window, hangmanGame);
            }
            else {
                hangmanGame.Draw(window);

                if (!isGameOverMenuVisible) {
                    sf::Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setCharacterSize(40);
                    gameOverText.setFillColor(sf::Color::Black);

                    if (hangmanGame.IsGameWon()) {
                        gameOverText.setString("You Win! Press Enter to continue or Esc to quit.");
                    }
                    else {
                        gameOverText.setString("You Lose! Press Enter to continue or Esc to quit.");
                    }

                    gameOverText.setPosition(200.f, 500.f);
                    gameOverText.setCharacterSize(30);

                    window.draw(gameOverText);
                    isGameOverMenuVisible = true;
                }

                if (isGameOverMenuVisible) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isGameOver = false;
                        isGameOverMenuVisible = false;
                        hangmanGame.Reset();
                        inGame = true;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        inMainMenu = true;
                        inGame = false;
                    }
                }
            }
        }
        std::cin.get();
        window.display();
    }

    return 0;
}