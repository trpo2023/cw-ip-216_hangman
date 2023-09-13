#include <stdio.h>

#define CTEST_MAIN
#define CTEST_COLOR_OK

#define CTEST_SEGFAULT

#include "../thirdparty/ctest.h"

int main(int argc, const char* argv[])
{
    chdir("../bin/resources/");
    int result = ctest_main(argc, argv);

    return result;
}