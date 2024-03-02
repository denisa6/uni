#include "Main.h"
#include "Matrix.h"
#include "ThreadPool.h"
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <future>
#include <chrono>


int Main::a, Main::b, Main::c;
Matrix Main::m1(a, b), Main::m2(b, c);
int Main::functionType, Main::scanType, Main::taskNumber;


void Main::getParams() {
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    std::cout << "c: ";
    std::cin >> c;
    std::cout << "function type:\n0. task\n1. task pool\n";
    std::cin >> functionType;
    std::cout << "scan type:\n0. row\n1. column\n2. kth elem\n";
    std::cin >> scanType;
    std::cout << "task number: ";
    std::cin >> taskNumber;
    genMatrix();
}

void Main::genMatrix() {
    m1 = Matrix(a, b);
    m2 = Matrix(b, c);
}

void Main::hardCodeParams() {/*
    a = 3;
    b = 2;
    c = 2;
    functionType = 0;
    scanType = 0;
    m1 = Matrix(std::vector<std::vector<int>>{
        {1, 2},
        { 3, 4 },
        { 5, 6 }
    });
    m2 = Matrix(std::vector<std::vector<int>>{
        {7, 8},
        { 9, 10 }
    });
    taskNumber = 3;*/
}

Matrix Main::productByTasks() {
    std::vector<std::thread> threads;
    int iterations = a * c / taskNumber;

    int** ans = new int* [a];
    for (int i = 0; i < a; ++i) {
        ans[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < taskNumber; ++i) {
        int left = i * iterations;
        int right = std::min((i + 1) * iterations, a * c);
        int localTaskNumber = taskNumber;
        if (functionType == 0)
            threads.emplace_back([left, right, &ans]() {
            RowThread rowThread(ans, left, right);
            rowThread.run();
                });
        else if (functionType == 1)
            threads.emplace_back([left, right, &ans]() {
            ColumnThread columnThread(ans, left, right);
            columnThread.run();
                });
        else
            threads.emplace_back([i, localTaskNumber, &ans]() {
            KthThread kthThread(ans, i, localTaskNumber);
            kthThread.run();
                });
    }

    for (auto& thread : threads)
        thread.join();

    return Matrix(ans, a, c);
}

Matrix Main::productByThreadPool() {
    int iterations = a * c / taskNumber;
    int threadNr = 32;
    int** ans = new int* [a];
    for (int i = 0; i < a; ++i) {
        ans[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            ans[i][j] = 0;
        }
    }
    ThreadPool pool(threadNr);
    for (int i = 0; i < taskNumber; ++i) {
        int left = i * iterations;
        int right = std::min((i + 1) * iterations, a * c);
        int localTaskNumber = taskNumber;
        if (functionType == 0)
            pool.enqueue([left, right, &ans]() {
            RowThread rowThread(ans, left, right);
            rowThread.run();
                });
        else if (functionType == 1)
            pool.enqueue([left, right, &ans]() {
            ColumnThread columnThread(ans, left, right);
            columnThread.run();
                });
        else
            pool.enqueue([i, localTaskNumber, &ans]() {
            KthThread kthThread(ans, i, localTaskNumber);
            kthThread.run();
                });
    }

    pool.close();
    return Matrix(ans, a, c);
}

void Main::run() {
    getParams();
    Matrix trueProduct = Matrix::getProductSequentially(m1, m2);
    Matrix computedProduct(a, c);

    auto start = std::chrono::high_resolution_clock::now();
    if (functionType == 0)
        computedProduct = productByTasks();
    else
        computedProduct = productByThreadPool();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (trueProduct == computedProduct)
        std::cout << "ok" << std::endl;
    else
        std::cout << "not ok" << std::endl;
    std::cout << duration.count() << std::endl;
}

int main() {
    Main::run();
    return 0;
}
