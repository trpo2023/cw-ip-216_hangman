#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("../resources/arial.ttf");
    playText.setFont(font);
    playText.setCharacterSize(40);
    playText.setString("Play");
    playText.setPosition(window.getSize().x / 2 - playText.getLocalBounds().width / 2, 500);

    exitText.setFont(font);
    exitText.setCharacterSize(40);
    exitText.setString("Exit");
    exitText.setPosition(window.getSize().x / 2 - exitText.getLocalBounds().width / 2, 550);

    selectedItem = MenuItem::Play;
    UpdateTextColors();
    backgroundTexture.loadFromFile("../resources/background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);
}
void MainMenu::HandleInput(sf::Event event, bool& inMainMenu, bool& inGame) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedItem = (selectedItem == MenuItem::Play) ? MenuItem::Exit : MenuItem::Play;
            UpdateTextColors();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedItem = (selectedItem == MenuItem::Exit) ? MenuItem::Play : MenuItem::Exit;
            UpdateTextColors();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedItem == MenuItem::Play) {
                inMainMenu = false;
                inGame = true;
            }
            else if (selectedItem == MenuItem::Exit) {
                window.close();
            }
        }
    }
}

void MainMenu::Draw() {
    window.clear(sf::Color::White);
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(playText);
    window.draw(exitText);

    window.display();
}

MainMenu::MenuItem MainMenu::GetSelectedItem() const {
    return selectedItem;
}

void MainMenu::UpdateTextColors() {
    sf::Color playColor = (selectedItem == MenuItem::Play) ? sf::Color::Red : sf::Color::Black;
    sf::Color exitColor = (selectedItem == MenuItem::Exit) ? sf::Color::Red : sf::Color::Black;

    playText.setFillColor(playColor);
    exitText.setFillColor(exitColor);
}