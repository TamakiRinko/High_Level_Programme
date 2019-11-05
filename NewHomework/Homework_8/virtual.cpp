#include<iostream>
#include<string>
using namespace std;
#define print(x) cout << x << endl
#define input(x) cin >> x

class A {
private:
    int x;
public:
    A(){}
    virtual ~A(){}
    void prints(){
        x = 20;
        print(x);
    }
};

class B :public A{
private:
    
public:
    B(){}
    
};



int main(int argc, char const *argv[]){
    A* aa = new B();
    aa->prints();
    return 0;
}