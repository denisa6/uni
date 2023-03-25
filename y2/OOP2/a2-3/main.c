#include <crtdbg.h>
#include <stdio.h>
#include "main.h"
#include "UI.h"
#include "Tests.h"

int main() {
    setbuf(stdout, NULL);
    testAll();
    start();
    _CrtDumpMemoryLeaks();
    return 0;
}