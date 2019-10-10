#include<iostream>
using namespace std;
const double eps = 1e-10;

class car_cost{
public:
    virtual double cost() = 0;  
};

class cost_by_time: public car_cost{
private:
    double minute;
public:
    cost_by_time(double x): minute(x){}
    ~cost_by_time(){}
    double cost(){
        //cout << minute << endl;
        int x;
        if(minute - (double)((int)minute) < eps){//minute为整数
            x = minute;
        }
        else{
            x = (int)minute + 1;//不满1minute按1minute计算
        }
        cout << x << endl;
        return x * 1.2;
    }
};

class cost_by_len_1: public car_cost{
private:
    double len;
public:
    cost_by_len_1(double x): len(x){}
    ~cost_by_len_1(){}
    double cost(){
        int x;
        if(len - (double)((int)len) < eps){
            x = len;
        }
        else{
            x = (int)len + 1;
        }
        return x * 2.7;
    }
};

class cost_by_len_2: public car_cost{
private:
    double len;
public:
    cost_by_len_2(double x): len(x){}
    ~cost_by_len_2(){}
    double cost(){
        if(len <= 2)    return 11;
        int x;
        if(len - (double)((int)len) < eps){
            x = len;
        }
        else{
            x = (int)len + 1;
        }
        x -= 2;
        return x * 2 + 11;
    }
};

int main(){
    double time, len;
    car_cost* cost[3];
    cout << "请输入预计行驶时间和路程:\n";
    cin >> time >> len;
    cost[0] = new cost_by_time(time);
    cost[1] = new cost_by_len_1(len);
    cost[2] = new cost_by_len_2(len);
    double result = 999999999;//实际开销
    int flag;//出行方式
    for(int i = 0; i < 3; ++i){
        if(result > cost[i]->cost()){
            flag = i;
            result = cost[i]->cost();
        }
    }
    cout << "最便宜的出行方式为:\n";
    switch(flag){
        case 0: cout << "A";    break;
        case 1: cout << "B";    break;
        case 2: cout << "C";    break;
    }
    cout << "方式，需支付" << result << "元\n";
    return 0;
}