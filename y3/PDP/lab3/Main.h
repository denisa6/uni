#pragma once
#include "Matrix.h"
#include "RowThread.h"
#include "ColumnThread.h"
#include "KthThread.h"

class Main {
public:
    static int a, b, c;
    static int functionType; // 0 - task, 1 - pool
    static int scanType; // 0 - row, 1 - column, 2 - kth
    static int taskNumber;
    static Matrix m1;
    static Matrix m2;

    static void getParams();
    static void genMatrix();
    static void hardCodeParams();
    static Matrix productByTasks();
    static Matrix productByThreadPool();

    static void run();
};
