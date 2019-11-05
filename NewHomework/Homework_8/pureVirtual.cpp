#include<iostream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

class A {
private:
    
public:
    A(){}
    virtual void f(){};
};

class B :public A{
private:
    
public:
    B(){}
    // virtual void f(){};
    void f2(){
        cout << "hola!" << endl;
    }
};

int main(int argc, char const *argv[]){
    A a;
    a.f();
    B b;
    b.f2();
    // b.f();

    return 0;
}