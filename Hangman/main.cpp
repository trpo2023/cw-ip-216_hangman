#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <map>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Hangman Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) // Замените на путь к вашему фоновому изображению
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    std::vector<std::string> words = { "hangman", "programming", "computer", "engine", "SFML", "NOONE", "MOVIE", "COMPLEMENT" };
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::string selectedWord = words[std::rand() % words.size()];

    std::string guessedWord(selectedWord.length(), '_');
    unsigned int attemptsLeft = 8; // Теперь 8 попыток
    bool gameWon = false;
    bool gameLost = false;

    sf::Text guessedText;
    guessedText.setFont(font);
    guessedText.setCharacterSize(40);
    guessedText.setPosition(300.f, 600.f);

    std::map<sf::Keyboard::Key, char> keyMap = {
        {sf::Keyboard::A, 'A'}, {sf::Keyboard::B, 'B'}, {sf::Keyboard::C, 'C'}, {sf::Keyboard::D, 'D'},
        {sf::Keyboard::E, 'E'}, {sf::Keyboard::F, 'F'}, {sf::Keyboard::G, 'G'}, {sf::Keyboard::H, 'H'},
        {sf::Keyboard::I, 'I'}, {sf::Keyboard::J, 'J'}, {sf::Keyboard::K, 'K'}, {sf::Keyboard::L, 'L'},
        {sf::Keyboard::M, 'M'}, {sf::Keyboard::N, 'N'}, {sf::Keyboard::O, 'O'}, {sf::Keyboard::P, 'P'},
        {sf::Keyboard::Q, 'Q'}, {sf::Keyboard::R, 'R'}, {sf::Keyboard::S, 'S'}, {sf::Keyboard::T, 'T'},
        {sf::Keyboard::U, 'U'}, {sf::Keyboard::V, 'V'}, {sf::Keyboard::W, 'W'}, {sf::Keyboard::X, 'X'},
        {sf::Keyboard::Y, 'Y'}, {sf::Keyboard::Z, 'Z'}
    };

    // Рисуем виселицу
    sf::RectangleShape gallows(sf::Vector2f(15.f, 400.f)); // Вертикальная палка виселицы
    gallows.setFillColor(sf::Color::White);
    gallows.setPosition(890.f, 200.f);

    // Рисуем горизонтальную и вертикальную палки для головы
    sf::RectangleShape horizontalBar(sf::Vector2f(140.f, 10.f));
    horizontalBar.setFillColor(sf::Color::White);
    horizontalBar.setPosition(890.f, 200.f);

    sf::RectangleShape verticalBar(sf::Vector2f(10.f, 100.f));
    verticalBar.setFillColor(sf::Color::White);
    verticalBar.setPosition(960.f, 200.f);

    // Рисуем человечка
    sf::CircleShape head(25.f); // Голова
    head.setFillColor(sf::Color::White);
    head.setPosition(940.f, 290.f);

    sf::RectangleShape body(sf::Vector2f(10.f, 100.f)); // Туловище
    body.setFillColor(sf::Color::White);
    body.setPosition(960.f, 340.f);

    sf::RectangleShape leftArm(sf::Vector2f(70.f, 10.f)); // Левая рука
    leftArm.setFillColor(sf::Color::White);
    leftArm.setPosition(920.f, 320.f);
    leftArm.rotate(45.f);

    sf::RectangleShape rightArm(sf::Vector2f(70.f, 10.f)); // Правая рука
    rightArm.setFillColor(sf::Color::White);
    rightArm.setPosition(965.f, 365.f);
    rightArm.rotate(-45.f);

    sf::RectangleShape leftLeg(sf::Vector2f(60.f, 10.f)); // Левая нога
    leftLeg.setFillColor(sf::Color::White);
    leftLeg.setPosition(970.f, 430.f);
    leftLeg.rotate(45.f);

    sf::RectangleShape rightLeg(sf::Vector2f(60.f, 9.f)); // Правая нога
    rightLeg.setFillColor(sf::Color::White);
    rightLeg.setPosition(920.f, 470.f);
    rightLeg.rotate(-45.f);

    std::vector<sf::Shape*> bodyParts = { &gallows, &horizontalBar, &verticalBar, &head, &body, &leftArm, &rightArm, &leftLeg, &rightLeg };
    int wrongGuesses = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close(); // Закрыть окно при нажатии "Esc"
                }
                else if (!gameWon && !gameLost)
                {
                    sf::Keyboard::Key key = event.key.code;
                    if (keyMap.find(key) != keyMap.end())
                    {
                        char input = keyMap[key];
                        bool correctGuess = false;
                        bool alreadyGuessed = false;
                        for (size_t i = 0; i < selectedWord.length(); ++i)
                        {
                            if (std::tolower(input) == std::tolower(selectedWord[i]))
                            {
                                if (guessedWord[i] == '_') {
                                    guessedWord[i] = selectedWord[i];
                                    correctGuess = true;
                                }
                                else {
                                    alreadyGuessed = true;
                                }
                            }
                        }

                        if (!correctGuess && !alreadyGuessed)
                        {
                            ++wrongGuesses;
                            if (wrongGuesses >= bodyParts.size()) {
                                gameLost = true;
                            }
                        }

                        if (guessedWord == selectedWord)
                            gameWon = true;
                    }
                }
            }
        }

        guessedText.setString(guessedWord);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(guessedText);

        if (!gameLost)
        {
            sf::Text attemptsLeftText("Attempts Left: " + std::to_string(bodyParts.size() - wrongGuesses), font, 20);
            attemptsLeftText.setPosition(10.f, 10.f);
            window.draw(attemptsLeftText);

            // Отрисовка частей тела
            for (int i = 0; i < wrongGuesses; ++i)
            {
                window.draw(*bodyParts[i]);
            }
        }
        else
        {
            sf::Text gameOverText("Game Over! The word was: " + selectedWord, font, 30);
            gameOverText.setPosition(400.f, 300.f);
            window.draw(gameOverText);

            // Отрисовка всех частей тела при проигрыше
            for (sf::Shape* bodyPart : bodyParts)
            {
                window.draw(*bodyPart);
            }
        }

        if (gameWon)
        {
            sf::Text victoryText("Congratulations! You've won!", font, 30);
            victoryText.setPosition(400.f, 300.f);
            window.draw(victoryText);
        }

        window.display();
    }

    return 0;
}
