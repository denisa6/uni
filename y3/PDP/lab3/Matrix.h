#pragma once
class Matrix {
public:
    Matrix(int** matrix, int n, int m);
    Matrix(int n, int m);
    int get(int i, int j) const;
    static int getCell(const Matrix& m1, const Matrix& m2, int a, int b);
    static Matrix getProductSequentially(const Matrix& m1, const Matrix& m2);
    void print() const;
    bool operator==(const Matrix& other) const;

private:
    int** matrix;
    int n;
    int m;
};
