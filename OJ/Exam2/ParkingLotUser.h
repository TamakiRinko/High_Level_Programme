//
// Created by rinko on 2019/10/11.
//

#ifndef EXAM2_PARKINGLOTUSER_H
#define EXAM2_PARKINGLOTUSER_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;
class ParkingLotUser;

class PackingLot{
private:

public:
    queue<ParkingLotUser*> waitQueue;
    queue<ParkingLotUser*> tempQueue;
    int lots[20];
    int curUser;
    int getLot();
    void remove(ParkingLotUser* parkingLotUser);
    void replace(int k);
    PackingLot();
};

class ParkingLotUser{
private:
    int status;
    int id;
    static int maxId;
public:
    ParkingLotUser();
    int tryEnter();
    int getStatus();
    void leave();
    bool operator==(ParkingLotUser& parkingLotUser);
    void setStatus(int k);
    int getId(){
        return id;
    }
    ~ParkingLotUser();
};

#endif //EXAM2_PARKINGLOTUSER_H
