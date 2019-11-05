#include<iostream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

class Base {
public:
    Base() { x = 1; }
    int fun() { cout << "haha" << endl;return x; }
    virtual void output(ostream &os) { os << x << endl; }
private:
    int x;
};
class Derived : public Base {
public:
    Derived() { y = 2; }
    void output(ostream &os) { os << " " << y << endl; }
private:
    int y;
};

int main(int argc, char const *argv[]){
    Base boj;
    Derived doj;
    Base *bp1 = &boj;
    Base *bp2 = &doj;
    Base &br1 = boj;
    Base &br2 = doj;
    boj.output(cout); //(a)
    doj.output(cout); //(b)
    bp1->fun(); //(c)
    bp2->fun(); //(d)
    br1.output(cout); //(e)
    br2.output(cout); //(f)
}