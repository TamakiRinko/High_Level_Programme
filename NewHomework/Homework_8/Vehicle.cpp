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
    virtual void drive() = 0;
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
    Vehicle* v = new AmphibianCar();
    v->drive();
    ((AmphibianCar*)v)->setFlag(true);
    v->drive();

    return 0;
}