# Компилятор и флаги
CC = g++
CFLAGS = -Wall -Wextra -Werror -Ithirdparty/ -Isrc/Hangman_lib -Ithirdparty/include -DSFML_STATIC
SFML_LIBS = -Lthirdparty/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio -lopengl32 -lfreetype -lwinmm -lgdi32
LIFE_SRC = src/Hangman_main/
LIBLIFE_SRC = src/Hangman_lib/
LIFE_OBJ = obj/src/Hangman_main/
LIBLIFE_OBJ = obj/src/Hangman_lib/
BIN = bin/
TEST_BIN = bin/Hangman_test/
TEST = test/
TEST_OBJ = obj/test/
THIRDPARTY = thirdparty/
RESOURCES_DIR = bin/resources/

SRCS := $(shell find $(LIFE_SRC) $(LIBLIFE_SRC) -type f -name '*.cpp')
HDRS := $(shell find $(LIFE_SRC) $(LIBLIFE_SRC) -type f -name '*.h')

.PHONY: main

$(BIN)Hangman_main/main.exe: $(LIFE_OBJ)main.o $(LIBLIFE_OBJ)liblife.a
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_LIBS) -L$(RESOURCES_DIR) -rpath=$(RESOURCES_DIR)

$(LIFE_OBJ)main.o: $(LIFE_SRC)main.cpp 
	$(CC) -c $(CFLAGS) -o $@ $^

$(LIBLIFE_OBJ)liblife.a: $(LIBLIFE_OBJ)HangmanGame.o $(LIBLIFE_OBJ)MainMenu.o 
	ar rcs $@ $^

$(LIBLIFE_OBJ)HangmanGame.o: $(LIBLIFE_SRC)HangmanGame.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

$(LIBLIFE_OBJ)MainMenu.o: $(LIBLIFE_SRC)MainMenu.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

.PHONY: test

test: $(TEST_BIN)test
	$(TEST_BIN)test

$(TEST_BIN)test: $(TEST_OBJ)ctest.o $(TEST_OBJ)main.o $(TEST_OBJ)testliblife.a 
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_LIBS) -L$(RESOURCES_DIR) -Wl,-rpath=$(RESOURCES_DIR)

$(TEST_OBJ)ctest.o: $(TEST)ctest.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

$(TEST_OBJ)main.o: $(TEST)main.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

$(TEST_OBJ)testliblife.a: $(TEST_OBJ)MainMenu.o $(TEST_OBJ)HangmanGame.o
	ar rcs $@ $^

$(TEST_OBJ)HangmanGame.o: $(LIBLIFE_SRC)HangmanGame.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

$(TEST_OBJ)MainMenu.o: $(LIBLIFE_SRC)MainMenu.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(LIFE_OBJ)*.o
	rm -rf $(LIBLIFE_OBJ)*.o
	rm -rf $(LIBLIFE_OBJ)*.a
	rm -rf $(TEST_OBJ)*.o
	rm -rf $(TEST_OBJ)*.a
	rm -rf $(BIN)*.exe

.PHONY: format

format:
	clang-format -i $(SRCS) $(HDRS)
