#include <SFML/Graphics.hpp>
#include "HangmanGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman Game");

    HangmanGame hangmanGame;
    hangmanGame.Init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
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

    return 0;
}
