#include<iostream>
using namespace std;

class Vehicle {
private:
    int weight;
    int num_of_passenger;
public:
    Vehicle(){}
    void setWeight(int weight){
        this->weight = weight;
    }
    void setNum(int num){
        this->num_of_passenger = num;
    }
    virtual void drive() = 0;                       //虚方法
};

class Car :public Vehicle{
private:
    
public:
    Car(){}
    void drive(){
        cout << "路上行驶!" << endl;
    }
};

class Ship :public Vehicle{
private:
    
public:
    Ship(){}
    void drive(){
        cout << "海上行驶!" << endl;
    }
};

class Airplane :public Vehicle{
private:
    
public:
    Airplane(){}
    void drive(){
        cout << "空中行驶!" << endl;
    }
};

class AmphibianCar :public Vehicle{
private:
    bool flag;
public:
    AmphibianCar(bool f = false): flag(f){}
    void drive(){
        if(flag){
            cout << "路上行驶!" << endl;  
        }
        else{
            cout << "海上行驶!" << endl;
        }
    }
    void setFlag(bool flag){
        this->flag = flag;
    }
};


int main(int argc, char const *argv[]){
    int x = 20;
    Vehicle* v = new AmphibianCar();            //默认为海上行驶
    v->drive();
    ((AmphibianCar*)v)->setFlag(true);          //改为路上行驶
    v->drive();

    cout << endl;
    Vehicle** vList = new Vehicle*[4];
    vList[0] = new Car();
    vList[1] = new Ship();
    vList[2] = new Airplane();
    vList[3] = new AmphibianCar();
    for(int i = 0; i < 4; ++i){
        vList[i]->drive();
    }

    return 0;
}