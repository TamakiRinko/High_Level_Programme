#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include <iostream>
//#include <string>
using namespace std;

class vehicle{
private:
    double weight;
public:
    vehicle(double w = 0): weight(w){cout << "载入Vehicle类构造函数\n";}
    virtual ~vehicle(){}
    vehicle(vehicle& x): weight(x.weight){}
    void setWeight(double x): weight(x){cout << "更新重量\n";}
    double getWeight(){return weight;}
    virtual void drive();
};

#endif
