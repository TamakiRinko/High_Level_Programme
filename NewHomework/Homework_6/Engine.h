#include<iostream>
using namespace std;

#define MAX_OIL 100

class Engine {
protected:
    double oil;
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
public:
    Engine(){}
    Engine(double initOil): oil(initOil){}
    
    virtual bool start() = 0;
    virtual bool stop() = 0;
};

class MotorEngine: public Engine {
protected:
    
public:
    MotorEngine(){}
    MotorEngine(double initOil): Engine(initOil){}
    bool addoil(double addOil){                                 //覆盖父类addoil方法
        if(Engine::open() && Engine::addoil(addOil) && Engine::close()){
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
};

enum Quality{
    BAD, NORMAL, GOOD
};

class AdvancedMotorEngine: public MotorEngine {
private:
    Quality quality;
public:
    AdvancedMotorEngine(){}
    AdvancedMotorEngine(double initOil, Quality initQuality): MotorEngine(initOil), quality(initQuality){}
    double display(){
        return oil;
    }
    bool checkoil(){
        return (quality == GOOD);
    }
};