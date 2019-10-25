#include "Matrix.h"

int main() {
    Matrix A(0, 3, 5);
    cout << A << endl;
    Matrix B = A;
    cout << B << endl;
    Matrix C(0, 5, 4);
    Matrix D = A % C;
    cout << D << endl;
    A = D = B;
    Matrix E(1, 5, 3);
    cout << B % E << endl;
    A[0][3] = 1;
    cout << A << endl;
    B = A.T();
    cout << B << endl;
    cout << Matrix(1, 2, 4) << endl;
//    Matrix P = (Matrix(1, 2, 4)%Matrix(0, 4, 3)) + Matrix(0, 2, 3);
//    cout << P << endl;
    cout << (Matrix(1, 2, 4)%Matrix(0, 4, 3)) + Matrix(0, 2, 3) << endl;
    cout << (Matrix(0, 2, 2) - Matrix(1, 2, 2)) << endl;
    cout << (Matrix(0, 2, 2) * Matrix(1, 2, 2)) << endl;
//    Matrix E(1, 5, 3);
//    cout << E << endl;
//    B = A.T();
//    cout << B << endl;
    return 0;
}