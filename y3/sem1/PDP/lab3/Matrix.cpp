#include "Matrix.h"
#include <iostream>
#include <random>

Matrix::Matrix(int** matrix, int n, int m) : matrix(matrix), n(n), m(m) {
}


Matrix::Matrix(int n, int m) : n(n), m(m) {
    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
}

int Matrix::get(int i, int j) const {
    return matrix[i][j];
}

int Matrix::getCell(const Matrix& m1, const Matrix& m2, int a, int b) {
    int ans = 0;
    for (int i = 0; i < m1.m; ++i) {
        ans += m1.get(a, i) * m2.get(i, b);
    }
    return ans;
}

Matrix Matrix::getProductSequentially(const Matrix& m1, const Matrix& m2){
    int** product = new int* [m1.n];
    for (int i = 0; i < m1.n; ++i) {
        product[i] = new int[m2.m];
    }
    for (int i = 0; i < m1.n; ++i) {
        for (int j = 0; j < m2.m; ++j) {
            product[i][j] = getCell(m1, m2, i, j);
        }
    }
    return Matrix(product, m1.n, m2.m);
}

void Matrix::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Matrix::operator==(const Matrix& other) const {
    if (n != other.n || m != other.m) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}
