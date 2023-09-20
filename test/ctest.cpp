#include "../src/hangman_lib/hangman.h"
#include "../src/hangman_lib/menu.h"
#include "ctest.h"
#include <iostream>
#include <sstream>

CTEST(Hangman_class, test1)
{
    Hangman game("easy");
    srand(123); 

    const std::string difficultyWord = game.getGuessedWord();

    for (char c : game.getCorrectGuessesAsString()) {
        ASSERT_TRUE(difficultyWord.find(c) != std::string::npos);
    }
}

CTEST(Hangman_class, test2)
{
    Hangman game("easy");
    
    game.setInitialWord("apple");

    // Проверяем отображение угаданных букв в слове
    game.updateGuessedWord('a');
    game.updateGuessedWord('p');
    game.updateGuessedWord('l');
    ASSERT_STR("appl_", game.getGuessedWord().c_str());
}

CTEST(Hangman_class, test3)
{
    Hangman game("medium");
    
    game.setInitialWord("kangaroo");

    // Проверяем отображение угаданных букв в слове
    game.updateGuessedWord('g');
    game.updateGuessedWord('o');
    game.updateGuessedWord('k');
    ASSERT_STR("k__g__oo", game.getGuessedWord().c_str());
}


CTEST(Hangman_class, test4)
{
    Hangman game("hard");
    
    game.setInitialWord("javascript");

    // Проверяем отображение угаданных букв в слове
    game.updateGuessedWord('a');
    game.updateGuessedWord('p');
    game.updateGuessedWord('t');
    ASSERT_STR("_a_a____pt", game.getGuessedWord().c_str());
}

CTEST(Hangman_class, test5)
{
    Hangman game("easy");
    
    game.setInitialWord("apple");

    // Проверяем, что счетчик оставшихся попыток уменьшается при неправильной букве
    game.updateGuessedWord('z');
    ASSERT_EQUAL(5, game.getRemainingAttempts());

    game.updateGuessedWord('y');
    ASSERT_EQUAL(4, game.getRemainingAttempts());
}

CTEST(Hangman_class, test6) {
    Hangman game("easy");
    
    game.setInitialWord("apple");

    game.updateGuessedWord('a');
    ASSERT_STR("a____", game.getGuessedWord().c_str());
}

CTEST(Hangman_class, test7) {
    Hangman game("easy");

    game.setInitialWord("apple");

    game.updateGuessedWord('z');
    game.updateGuessedWord('y');
    game.updateGuessedWord('x');
    game.updateGuessedWord('w');
    game.updateGuessedWord('v');
    game.updateGuessedWord('u');

    ASSERT_TRUE(game.isGameOver());
    ASSERT_FALSE(game.isGameWon());
}

CTEST(Hangman_class, test8) {
    Hangman game("easy");
    
    game.setInitialWord("apple");

    // Угадываем все буквы, чтобы выиграть игру
    game.updateGuessedWord('a');
    game.updateGuessedWord('p');
    game.updateGuessedWord('l');
    game.updateGuessedWord('e');
    ASSERT_TRUE(game.isGameWon());
}

