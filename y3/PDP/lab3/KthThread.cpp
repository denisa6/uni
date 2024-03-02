#include "KthThread.h"
#include "Main.h" // Include the appropriate header for your Main class

KthThread::KthThread(int** ans, int k, int stepSize) : ans(ans), k(k), stepSize(stepSize) {
}

void KthThread::run() {
    int n = Main::a;
    int m = Main::c;
    int i = 0;
    int j = k;
    while (true) {
        int overshoot = j / m;
        i += overshoot;
        j -= overshoot * m;
        if (i >= n)
            break;
        ans[i][j] = Matrix::getCell(Main::m1, Main::m2, i, j);
        j += stepSize;
    }
}
