#include "../thirdparty/ctest.h"
#include "../src/Hangman_lib/HangmanGame.h"
#include "../src/Hangman_lib/MainMenu.h"

CTEST(HangmanGameTest, IsGameOverInitiallyFalse) {
    HangmanGame game;
    game.Init();

    ASSERT_FALSE(game.IsGameOver());
}

CTEST(HangmanGameTest, IsGameWonInitiallyFalse) {
    HangmanGame game;
    game.Init();
    ASSERT_FALSE(game.IsGameWon());
}

CTEST(MainMenuTest, SelectPlayItemInitially) {
    sf::RenderWindow window;
    MainMenu menu(window);

    ASSERT_STR(menu.GetSelectedItem() == MainMenu::MenuItem::Play ? "Play" : "Exit", "Play");
}

CTEST(MainMenuTest, HandleInputSelectExitItem) {
    sf::RenderWindow window;
    MainMenu menu(window);

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Down;
    bool inMainMenu = true;
    bool inGame = false;
    menu.HandleInput(event, inMainMenu, inGame);

    ASSERT_STR(menu.GetSelectedItem() == MainMenu::MenuItem::Exit ? "Exit" : "Play", "Exit");
}


CTEST(HangmanGameTest, InitialSecretWordNotEmpty) {
    HangmanGame game;
    game.Init();

    ASSERT_FALSE(game.GetSecretWord().empty());
}

CTEST(HangmanGameTest, InitialGuessedWordEmpty) {
    HangmanGame game;
    game.Init();

    ASSERT_TRUE(game.GetGuessedWord() == std::string(game.GetSecretWord().length(), '_'));
}

CTEST(HangmanGameTest, CorrectGuessUpdatesGuessedWord) {
    HangmanGame game;
    game.Init();
    char correctGuess = game.GetSecretWord()[0];
    game.ProcessInput(correctGuess);
    std::string guessedWord = game.GetGuessedWord();

    ASSERT_TRUE(guessedWord[0] == correctGuess);
}

CTEST(HangmanGameTest, IncorrectGuessReducesAttempts) {
    HangmanGame game;
    game.Init();
    char incorrectGuess = 'z'; // Предполагаем, что 'z' является неправильной догадкой
    int initialAttempts = game.GetAttemptsLeft();
    game.ProcessInput(incorrectGuess);
    int attemptsAfterIncorrectGuess = game.GetAttemptsLeft();

    ASSERT_TRUE(attemptsAfterIncorrectGuess == (initialAttempts - 1));
}

CTEST(MainMenuTest, InitialSelectedItemIsPlay) {
    sf::RenderWindow window;
    MainMenu menu(window);

    ASSERT_TRUE(menu.GetSelectedItem() == MainMenu::MenuItem::Play);
}

CTEST(MainMenuTest, HandleInputSelectPlayItem) {
    sf::RenderWindow window;
    MainMenu menu(window);

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Enter;
    bool inMainMenu = true;
    bool inGame = false;
    menu.HandleInput(event, inMainMenu, inGame);

    ASSERT_FALSE(inMainMenu);
    ASSERT_TRUE(inGame);
}