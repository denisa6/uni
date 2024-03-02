#include "ColumnThread.h"
#include "Main.h" // Include the appropriate header for your Main class

ColumnThread::ColumnThread(int** ans, int left, int right) : ans(ans), left(left), right(right) {
}

void ColumnThread::run() {
    int n = Main::a;
    int m = Main::c;
    int i = left % n;
    int j = left / n;
    int k = right - left;

    for (int index = 0; index < k; ++index) {
        ans[i][j] = Matrix::getCell(Main::m1, Main::m2, i, j);
        ++i;

        if (i == n) {
            i = 0;
            ++j;
        }
    }
}
