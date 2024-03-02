#include "RowThread.h"
#include "Main.h" // Include the appropriate header for your Main class

RowThread::RowThread(int** ans, int left, int right) : ans(ans), left(left), right(right) {
}

void RowThread::run() {
    int n = Main::a;
    int m = Main::c;
    int i = left / m;
    int j = left % m;
    int k = right - left;

    for (int index = 0; index < k; ++index) {
        ans[i][j] = Matrix::getCell(Main::m1, Main::m2, i, j);
        ++j;

        if (j == m) {
            j = 0;
            ++i;
        }
    }
}
