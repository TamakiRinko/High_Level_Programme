#include<iostream>
using namespace std;

#define MAX_OIL 100

enum Quality{
    UNKNOWN, BAD, NORMAL, GOOD
};

class Engine {
protected:
    double oil;
    Quality quality;
public:
    Engine(){}
    Engine(double initOil): oil(initOil), quality(UNKNOWN){}
    Engine(double initOil, Quality initQuality): oil(initOil), quality(initQuality){}
    bool open(){
        return true;
    }
    bool close(){
        return false;
    }
    bool addoil(double addOil){
        if(oil + addOil <= MAX_OIL){
            oil += addOil;
            return true;
        }
        return false;
    }
    bool start(){
        return true;
    }
    bool stop(){
        return true;
    }
    double display(){
        return oil;
    }
    bool checkoil(){
        return (quality == GOOD);
    }
};

class Motor {
protected:
    Engine e;                                               //聚合，摩托车中有引擎
public:
    Motor(double initOil): e(initOil){}
    Motor(double initOil, Quality initQuality): e(initOil, initQuality){}
    bool addoil(double addOil){                             //摩托车加油成功需要引擎三步都成功
        if(e.open() && e.addoil(addOil) && e.close()){
            return true;
        }
        return false;
    }
    bool run(){                                             //摩托车开动
        return (e.start() && e.stop());
    }
};

class AdvancedMotor :public Motor{                          //继承，高级摩托车是特殊的摩托车
private:
    
public:
    AdvancedMotor(double initOil, Quality initQuality): Motor(initOil, initQuality){}
    double display(){
        return e.display();
    }
    bool checkoil(){
        return e.checkoil();
    }
};

int main(){
    AdvancedMotor ad(20, GOOD);
    cout << ad.display() << endl;
    ad.addoil(200);
    cout << ad.display() << endl;
    ad.addoil(50);
    cout << ad.display() << endl;
    cout << ad.checkoil() << endl;

    Motor m(10);
    m.addoil(20);
    m.run();
}