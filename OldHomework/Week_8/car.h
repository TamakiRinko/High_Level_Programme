#ifndef _CAR_H_
#define _CAR_H_

#include "vehicle.h"

class car: virtual public vehicle{
private:
    double air_out;
public:
    car(double w, double air): vehicle(w), air_out(air){cout << "载入Car类构造函数\n";}
    ~car(){}
    car(car& x): vehicle(x), air_out(x.air_out){}
    void drive(){cout << "我在陆地上行驶!\n";}
    double getAir(){return air_out;}
};


#endif
