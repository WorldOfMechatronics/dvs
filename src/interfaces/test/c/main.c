#include <stdio.h>

#include "cb_tests.h"
#include "duoplot/duoplot.h"
#include "tests.h"

int main()
{
    runTests();
    runCbTests();

    printf("All tests passed!\n");
    return 0;
}
