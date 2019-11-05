#include<iostream>
#include<string>
using namespace std;

class A {
private:
    
public:
    A(){}
    virtual void f1(int x){
        cout << "hola!" << endl;
    }
};

class B :public A{
private:
    
public:
    B(){}
    void f1(int x){
        cout << "hello!" << endl;
    }
};

#define print(x) cout << x << endl
#define input(x) cin >> x

int main(int argc, char const *argv[]){
    A* a = new B();
    a->f1(3);
    return 0;
}