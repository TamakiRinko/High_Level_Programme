#include<iostream>
#include<math.h>
using namespace std;

class Polygon {
public:
    Polygon(){}
    virtual double primeter() = 0;              //纯虚函数，子类重写
    virtual double area() = 0;
};

class Rectangle: public Polygon{
private:
    double x;
    double y;
public:
    Rectangle(double x, double y){
        this->x = x;
        this->y = y;
    }
    double primeter(){
        return (x + y) * 2;
    }
    double area(){
        return x * y;
    }
};

class Triangle: public Polygon {
private:
    double a;
    double b;
    double c;
public:
    Triangle(double a, double b, double c){
        this->a = a;
        this->b = b;
        this->c = c;
    }
    double primeter(){
        return a + b + c;
    }
    double area(){
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class Trapezoid: public Polygon {
private:
    double bottom1;
    double bottom2;
    double waist1;
    double waist2;
public:
    Trapezoid(double bottom1, double bottom2, double waist1, double waist2){
        this->bottom1 = bottom1;
        this->bottom2 = bottom2;
        this->waist1 = waist1;
        this->waist2 = waist2;
    }
    double primeter(){
        return bottom1 + bottom2 + waist1 + waist2;
    }
    double area(){
        double shortOne;
        double remain;
        if(bottom1 > bottom2){
            shortOne = bottom2;
            remain = bottom1 - bottom2;
        }else{
            shortOne = bottom1;
            remain = bottom2 - bottom1;
        }
        double p = (waist1 + waist2 + remain) / 2;
        double S1 = sqrt(p * (p - waist1) * (p - waist2) * (p - remain));
        double h = S1 * 2 / remain;
        double S2 = h * shortOne;
        return S1 + S2;
    }
};

