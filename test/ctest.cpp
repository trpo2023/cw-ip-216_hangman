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

