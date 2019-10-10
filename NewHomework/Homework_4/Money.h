#include<iostream>
using namespace std;
class Money {
private:
    int y;
    int j;
    int f;
public:
    Money(int y, int j, int f){
        this->y = y;
        this->j = j;
        this->f = f;
    }
    friend Money operator+(const Money& m1, const Money& m2);
    friend Money operator-(const Money& m1, const Money& m2);
};
