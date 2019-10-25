//
// Created by rinko on 2019/10/25.
//

#ifndef EXAM3_MATRIX_H
#define EXAM3_MATRIX_H

#include <iostream>
using namespace std;

class Matrix {
private:
    int* elements;
    int row;
    int column;
    int len;
public:
    Matrix();
    Matrix(int row, int column);
    Matrix(int seed, int row, int column);
    ~Matrix();
    Matrix T();
    //成员函数重载
    Matrix(const Matrix& m);
    int* operator[](int i);
    Matrix& operator=(const Matrix& m);
    Matrix operator%(const Matrix& m);
    //友元函数重载
    friend ostream& operator <<(ostream& out, Matrix m);
    friend Matrix operator+(Matrix m1, Matrix m2);
    friend Matrix operator-(Matrix m1, Matrix m2);
    friend Matrix operator*(Matrix m1, Matrix m2);
};


#endif //EXAM3_MATRIX_H
