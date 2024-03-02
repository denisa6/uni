#pragma once
class RowThread {
public:
    RowThread(int** ans, int left, int right);
    void run();

private:
    int** ans;
    int left;
    int right;
};
