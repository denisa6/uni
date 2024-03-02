#pragma once
class KthThread {
public:
    KthThread(int** ans, int k, int stepSize);
    void run();

private:
    int** ans;
    int k;
    int stepSize;
};
