#ifndef _AMPHIBIANCAR_H_
#define _AMPHIBIANCAR_H_

#include "vehicle.h"
#include "car.h"
#include "boat.h"

class amphibiancar: public car, public boat{
private:
    bool flag;
public:
    amphibiancar(double w, double air, double water, bool f):
     vehicle(w), car(w, air), boat(w, water), flag(f){cout << "载入AmphibianCar类构造函数\n";}
    ~amphibiancar(){}
    amphibiancar(amphibiancar& x): vehicle(x), boat(x), car(x), flag(x.flag){}
    void setFlags(bool f): flag(f){cout << "更新状态变量\n";}
    void drive(){
        if(flag == true)
            cout << "我在陆地上行驶!\n";
        else
            cout << "我在陆地上行驶!\n";
    }
    void showMembers(){
        cout << "重量: " << getWeight() << "吨, "
        << "空气排量: " << getAir() << "CC, "
        << "排水量: " << getWater() << "吨, "
        << "flag: " << flag << endl;
    }
};


#endif
