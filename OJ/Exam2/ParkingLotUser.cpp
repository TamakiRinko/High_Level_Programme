//
// Created by rinko on 2019/10/11.
//

#include "ParkingLotUser.h"

PackingLot packingLot;
int ParkingLotUser::maxId = 0;

ParkingLotUser::ParkingLotUser() {
    id = maxId;
    maxId++;
    status = -1;
}

int ParkingLotUser::tryEnter() {
    if(status == -1){
        if(packingLot.curUser == 20){                      //full
            packingLot.waitQueue.push(this);
            status = 0;
            return 0;
        }else{
            status = packingLot.getLot();
            return status;
        }
    }else if(status >= 0){                              //already
        return -2;
    }
    return -1;
}

void ParkingLotUser::leave() {
    if(status == -1){
        return;
    }else if(status == 0) {
        packingLot.remove(this);
        status = -1;
    }else{
        packingLot.replace(status);
        status = -1;
    }
}

int ParkingLotUser::getStatus() {
    return status;
}

ParkingLotUser::~ParkingLotUser() {
    leave();
}

bool ParkingLotUser::operator==(ParkingLotUser &parkingLotUser) {
    return (this->id == parkingLotUser.id);
}

void ParkingLotUser::setStatus(int k) {
    this->status = k;
}


PackingLot::PackingLot() {
    for(int i = 0; i < 20; ++i){
        lots[i] = 0;
    }
    curUser = 0;
}

int PackingLot::getLot() {
    for(int i = 0; i < 20; ++i){
        if(lots[i] == 0){
            lots[i] = 1;
            curUser++;
            return i + 1;
        }
    }
    return -1;
}

void PackingLot::remove(ParkingLotUser* parkingLotUser) {
    while(!waitQueue.empty()){
        if(waitQueue.front()->getId() == parkingLotUser->getId()){
            waitQueue.front()->setStatus(-1);
            waitQueue.pop();
        }else{
            tempQueue.push(waitQueue.front());
            waitQueue.pop();
        }
    }
    while(!tempQueue.empty()){
        waitQueue.push(tempQueue.front());
        tempQueue.pop();
    }
}

void PackingLot::replace(int k) {
    if(!waitQueue.empty()){
        waitQueue.front()->setStatus(k);
        waitQueue.pop();
    }else{
        lots[k - 1] = 0;
        curUser--;
    }
}
