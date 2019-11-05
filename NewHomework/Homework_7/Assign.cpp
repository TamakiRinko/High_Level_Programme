#include <iostream>
#include <cstring>
using namespace std;

class A{
private:
    int x;
public:
    A(int x){
        this->x = x;
    }
    A& operator=(const A& a){           //定义基类拷贝构造函数
        x = a.x;
        return *this;
    }
    int get_x(){
        return x;
    }
};

class B: public A{
private:
    char* str;
public:
    B(int x, int length, char* s):A(x){
        str = new char[length+1];
        for(int i = 0;i<length;i++)
            str[i]=s[i];
        str[length]='\0';
    }
    B& operator=(const B& b){           //定义派生类拷贝构造函数
        this->A::operator=(b);          //调用基类自定义的拷贝构造
        if(str!=NULL){
            delete[] str;
            str = NULL;
        }
        int length = strlen(b.str);
        str = new char[length + 1];
        for(int i = 0;i < length; i++)
            str[i] = (b.str)[i];
        str[length] = '\0';
        return *this;
    }
    ~B(){
        if(str!=NULL){
            delete[] str;
            str = NULL;
        }
    } 
    void print(){
        cout << this->str << "," << this->get_x() << endl;
    }
};

void f(){
    B b1(10, 5, (char*)"Hello"), b2(20, 5, (char*)"World");
    b1.print();
    b2.print();
    b1 = b2;
    b1.print();
    b2.print();
}

int main(){
    f();
    cout<<"Hello World"<<endl;
    return 0;
}