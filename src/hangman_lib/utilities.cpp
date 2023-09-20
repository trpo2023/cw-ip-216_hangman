#include "utilities.h"
#include <iostream>

void clearScreen() {
    std::cout << "\033[H\033[J";
}
