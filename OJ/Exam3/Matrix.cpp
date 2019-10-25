//
// Created by rinko on 2019/10/25.
//

#include "Matrix.h"

Matrix::Matrix(int seed, int row, int column) {
    len = row * column;
    this->column = column;
    this->row = row;
    elements = new int[len];
    if(seed == 0){
        for(int i = 0; i < len; ++i){
            if(i % 3 == 1){
                elements[i] = 1;
            }else{
                elements[i] = 0;
            }
        }
    }else if(seed == 1){
        for(int i = 0; i < len; ++i){
            if(i % 3 == 2){
                elements[i] = 0;
            }else{
                elements[i] = 1;
            }
        }
    }
}

Matrix::Matrix(int row, int column) {
    len = row * column;
    this->column = column;
    this->row = row;
    elements = new int[len];
    for(int i = 0; i < len; ++i){
        elements[i] = 0;
    }
}

ostream& operator<<(ostream& out, Matrix m) {
    for(int i = 0; i < m.row; ++i){
        for(int j = 0; j < m.column; ++j){
            out << m.elements[i * m.column + j];
        }
        out << endl;
    }
    return out;
}

int* Matrix::operator[](int i) {
    int* thisrow = elements + i * column;
    return thisrow;
}

Matrix::Matrix(const Matrix &m) {
    len = m.len;
    column = m.column;
    row = m.row;
    elements = new int[len];
    for(int i = 0; i < len; ++i){
        elements[i] = m.elements[i];
    }
}

Matrix::Matrix() {
    elements = NULL;
    column = 0;
    row = 0;
    len = 0;
}

Matrix& Matrix::operator=(const Matrix &m) {
    if(&m == this){
        return *this;
    }
    if(len != 0){
        delete elements;
    }
    len = m.len;
    row = m.row;
    column = m.column;
    elements = new int[len];
    for(int i = 0; i < len; ++i){
        elements[i] = m.elements[i];
    }
    return *this;
}

Matrix Matrix::T() {
    Matrix m(column, row);
    for(int i = 0; i < column; ++i){
        for(int j = 0; j < row; ++j){
            m[i][j] = (*this)[j][i];
        }
    }
    return m;
}

Matrix Matrix::operator%(const Matrix &m){
    Matrix result(row, m.column);
    for(int i = 0; i < result.row; ++i){
        for(int j = 0; j < result.column; ++j){
            for(int k = 0; k < column; ++k){
                result[i][j] = result[i][j] ^ (elements[i * column + k] & m.elements[k * m.column + j]);
            }
        }
    }
    return result;
}

Matrix operator+(Matrix m1, Matrix m2) {
    Matrix m3(m1.row, m1.column);
    for(int i = 0; i < m3.row; ++i){
        for(int j = 0; j < m3.column; ++j){
            m3[i][j] = m1[i][j] ^ m2[i][j];
        }
    }
    return m3;
}

Matrix operator-(Matrix m1, Matrix m2) {
    Matrix m3 = m1 + m2;
    return m3;
}

Matrix operator*(Matrix m1, Matrix m2) {
    Matrix m3(m1.row, m1.column);
    for(int i = 0; i < m3.row; ++i){
        for(int j = 0; j < m3.column; ++j){
            m3[i][j] = m1[i][j] & m2[i][j];
        }
    }
    return m3;
}

Matrix::~Matrix() {
    if(len != 0){
        delete elements;
    }
}


