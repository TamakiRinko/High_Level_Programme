#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<random>
#include<vector>
#include<time.h>
using namespace std;

class Matrix{
public:
    Matrix(int r, int c, bool flag);
    ~Matrix();
    Matrix* operator+(Matrix& m);
    Matrix* operator-(Matrix& m);
    Matrix* operator*(Matrix& m);
    Matrix* transpose();
    int getInt(int i, int j);
    double getDouble(int i, int j);
    bool getIsInt(){
        return isInt;
    }
    int getRow(){
        return row;
    }
    int getCol(){
        return col;
    }
private:
    double** matrixDouble;
    int** matrixInt;
    int row;
    int col;
    bool isInt;
};

#endif // MATRIX_H
