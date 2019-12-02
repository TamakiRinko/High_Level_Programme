#include "matrix.h"

Matrix::Matrix(int r, int c, bool flag){
    row = r;
    col = c;
    isInt = flag;

    if(flag){               //整数
        matrixDouble = nullptr;
        matrixInt = new int*[row];
        for(int i = 0; i < row; ++i){
            matrixInt[i] = new int[col];
        }
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j){
                matrixInt[i][j] = rand() % 100;
            }
        }
    }else{
        matrixInt = nullptr;
        matrixDouble = new double*[row];
        for(int i = 0; i < row; ++i){
            matrixDouble[i] = new double[col];
        }
        default_random_engine e(time(nullptr));
        uniform_real_distribution<double> u(0u, 100.0);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                matrixDouble[i][j] = u(e);
            }
        }
    }
}

Matrix::~Matrix(){
    if(isInt){
        for(int i = 0; i < row; ++i){
            delete matrixInt[i];
        }
        delete matrixInt;
    }else{
        for(int i = 0; i < row; ++i){
            delete matrixDouble[i];
        }
        delete matrixDouble;
    }
}


Matrix* Matrix::operator+(Matrix& m){
    if(m.row != row || m.col != col){
        return nullptr;
    }
    Matrix* result;
    if(m.isInt && isInt){
        result = new Matrix(row, col, true);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixInt[i][j] = matrixInt[i][j] + m.matrixInt[i][j];
            }
        }
    }else if(isInt){
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixInt[i][j] + m.matrixDouble[i][j];
            }
        }
    }else if(m.isInt){
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixDouble[i][j] + m.matrixInt[i][j];
            }
        }
    }else{
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixDouble[i][j] + m.matrixDouble[i][j];
            }
        }
    }
    return result;
}

Matrix* Matrix::operator-(Matrix& m){
    if(m.row != row || m.col != col){
        return nullptr;
    }
    Matrix* result;
    if(m.isInt && isInt){
        result = new Matrix(row, col, true);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixInt[i][j] = matrixInt[i][j] - m.matrixInt[i][j];
            }
        }
    }else if(isInt){
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixInt[i][j] - m.matrixDouble[i][j];
            }
        }
    }else if(m.isInt){
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixDouble[i][j] - m.matrixInt[i][j];
            }
        }
    }else{
        result = new Matrix(row, col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                result->matrixDouble[i][j] = matrixDouble[i][j] - m.matrixDouble[i][j];
            }
        }
    }
    return result;
}

Matrix* Matrix::operator*(Matrix& m){
    if(col != m.row){
        return nullptr;
    }
    Matrix* result;
    if(m.isInt && isInt){
        result = new Matrix(row, m.col, true);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < m.col; ++j){
                result->matrixInt[i][j] = 0;
                for(int k = 0; k < col; ++k){
                    result->matrixInt[i][j] += matrixInt[i][k] * m.matrixInt[k][j];
                }
            }
        }
    }else if(isInt){
        result = new Matrix(row, m.col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < m.col; ++j){
                result->matrixDouble[i][j] = 0;
                for(int k = 0; k < col; ++k){
                    result->matrixDouble[i][j] += matrixInt[i][k] * m.matrixDouble[k][j];
                }
            }
        }
    }else if(m.isInt){
        result = new Matrix(row, m.col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < m.col; ++j){
                result->matrixDouble[i][j] = 0;
                for(int k = 0; k < col; ++k){
                    result->matrixDouble[i][j] += matrixDouble[i][k] * m.matrixInt[k][j];
                }
            }
        }
    }else{
        result = new Matrix(row, m.col, false);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < m.col; ++j){
                result->matrixDouble[i][j] = 0;
                for(int k = 0; k < col; ++k){
                    result->matrixDouble[i][j] += matrixDouble[i][k] * m.matrixDouble[k][j];
                }
            }
        }
    }
    return result;
}

Matrix* Matrix::transpose(){
    Matrix* result = new Matrix(col, row, isInt);
    for(int i = 0; i < col; ++i){
        for(int j = 0; j < row; ++j){
            if(isInt){
                result->matrixInt[i][j] = matrixInt[j][i];
            }else{
                result->matrixDouble[i][j] = matrixDouble[j][i];
            }
        }
    }
    return result;
}

int Matrix::getInt(int i, int j){
    return matrixInt[i][j];
}

double Matrix::getDouble(int i, int j){
    return matrixDouble[i][j];
}
