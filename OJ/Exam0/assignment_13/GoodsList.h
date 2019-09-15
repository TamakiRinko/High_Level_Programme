//
// Created by TamakiRinko on 2019/9/14.
//

#include <string>
#include<iostream>
using namespace std;
class Goods{
private:
    string name;
    int nums;
public:
    Goods(){}
    Goods(string name, int nums);
    string getName(){
        return this->name;
    }
    int getNum(){
        return this->nums;
    }
    void increaseNum(int num){
        this->nums += num;
    }
    void decreaseNum(int num){
        this->nums -= num;
    }
    void show();
    ~Goods();
};


class GoodsList{
private:
    struct Node{
        Goods* goods;
        Node* next;
        Node(){
            goods = NULL;
            next = NULL;
        }
    } *list;
public:
    GoodsList();
    void insert(Goods* goods);
    void remove(string name, int nums);
    void show();
    void sort();
    int count();
    void clear();
    ~GoodsList();
};

