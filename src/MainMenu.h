#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
public:
    enum class MenuItem {
        Play,
        Exit
    };
    MainMenu(sf::RenderWindow& window);
    void HandleInput(sf::Event event, bool& inMainMenu, bool& inGame);
    void Draw();
    MenuItem GetSelectedItem() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text exitText;
    MenuItem selectedItem;
    bool shouldRedraw;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void UpdateTextColors();
};
