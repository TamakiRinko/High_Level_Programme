#ifndef _BOAT_H_
#define _BOAT_H_

#include "vehicle.h"

class boat: virtual public vehicle{
private:
    double water_out;
public:
    boat(double w, double water): vehicle(w), water_out(water){cout << "载入Boat类构造函数\n";}
    ~boat(){}
    boat(boat& x): vehicle(x), water_out(x.water_out){}
    void drive(){cout << "我在水上行驶!\n";}
    double getWater(){return water_out;}
};


#endif
