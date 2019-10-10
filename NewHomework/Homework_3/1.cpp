#include <iostream>
#include <cstring>
using namespace std;

class Matrix{ 
private:
    int dim;
    double *m_data;
public:
    Matrix(int d);
    Matrix(const Matrix& m);
    ~Matrix();
};
Matrix::Matrix(int d){
    dim = d;
    m_data = new double[dim*dim];
    cout << "Matrix" << endl;
}

Matrix::~Matrix(){
    cout << "~Matrix " << m_data << endl;  
    delete [] m_data;
    m_data = NULL;
}

Matrix::Matrix(const Matrix& m){
    dim = m.dim;                        //普通变量直接复制
    m_data = new double[dim * dim];     //重新申请内存区域
}
int main(){
    {
        Matrix m1(5);
        Matrix m2(m1);
    }
    system("pause");
    return 0;
}
