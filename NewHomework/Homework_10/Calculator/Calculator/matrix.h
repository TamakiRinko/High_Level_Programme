#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<random>
#include<vector>
using namespace std;

class Matrix
{
public:
    Matrix(){}
    virtual ~Matrix(){}
    virtual Matrix* add(Matrix& m1);
};

class MatrixInt: public Matrix{
public:
    MatrixInt(int r, int c);
    Matrix* add(Matrix& m1);
private:
    int** matrix;
    int row;
    int col;
};

class MatrixDouble: public Matrix{
public:
    MatrixDouble(int r, int c);
    Matrix* add(Matrix& m1);
private:
    double** matrix;
    int row;
    int col;
};

#endif // MATRIX_H
