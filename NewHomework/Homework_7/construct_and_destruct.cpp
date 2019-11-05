#include<iostream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

int num = 0;

class Member {
private:
    int n;
public:
    Member(){
        cout << "member construct" << endl;
        n = num;
        num++;
    }
    Member(const Member& M){
        cout << "member copy construct" << endl;
        n = num;
        num++;
    }
    ~Member(){
        cout << "member destruct" << n << endl;
    }
};

class Base {
private:
    int n;
public:
    Base(){
        cout << "base construct" << endl;
        n = num;
        num++;
    }
    Base(const Base& B){
        cout << "base copy construct" << endl;
        n = num;
        num++;
    }
    ~Base(){
        cout << "base destruct" << n << endl;
    }
};

class Derived :Base{
private:
    Member m1, m2;
    int n;
public:
    Derived(Member mm1, Member mm2): m1(mm1), m2(mm2){
        cout << "derived construct" << endl;
        n = num;
        num++;
    }
    Derived(const Derived& D){
        cout << "derived copy construct" << endl;
        n = num;
        num++;
    }
    ~Derived(){
        cout << "derived destruct" << n << endl;
    }
};

int main(int argc, char const *argv[]){
    Member m1;
    Member m2;
    Derived d1(m1, m2);
    Derived d2(d1);

    return 0;
}