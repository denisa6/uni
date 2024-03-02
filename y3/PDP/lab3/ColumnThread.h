#pragma once
class ColumnThread {
public:
    ColumnThread(int** ans, int left, int right);
    void run();

private:
    int** ans;
    int left;
    int right;
};
