#include <ctest.h>
#include "../src/HangmanGame.h"

CTEST(HangmanGameTest, IsGameOverInitiallyFalse) {
    HangmanGame game;
    game.Init();

    // Проверяем, что игра не завершена при инициализации.
    ASSERT_FALSE(game.IsGameOver());
}

