//
// Created by TamakiRinko on 2019/9/27.
//


#include "CainiaoSystem.hpp"

CainiaoSystem::CainiaoSystem() {

}

void CainiaoSystem::next_day() {
    dispatch.next_day();
    storage.next_day();
    list<goods>temp(dispatch.getGood());
    for(iter = temp.begin(); iter != temp.end(); ++iter){
        storage.add(iter);
    }
    dispatch.kill();
}

void CainiaoSystem::receive(int id) {
    storage.receive(id);
}

void CainiaoSystem::snap() {
    dispatch.snap();
    storage.snap();
}

void CainiaoSystem::show_storage() {
    storage.show();
}

void CainiaoSystem::show_dispatch() {
    dispatch.show();
}

void CainiaoSystem::send(int id, string sender, string receiver, int arrive_time) {
    dispatch.send(id, sender, receiver, arrive_time);
}

CainiaoSystem::~CainiaoSystem() {

}


Storage::Storage() {
    curDays = 0;
}

void Storage::next_day() {
    curDays++;
}

void Storage::receive(int id) {
    for(iter = storageList.begin(); iter != storageList.end(); ++iter){
        if(iter->id == id){
            cout << iter->sender << "," << iter->receiver << endl;
            storageList.erase(iter);
            return;
        }
    }
    cout << "tan90" << endl;
}

void Storage::show() {
    for(iter = storageList.begin(); iter != storageList.end(); ++iter){
        cout << iter->id << "," << iter->sender << "," << iter->receiver << "," << curDays - iter->timeArrivedSto << endl;
    }
}

void Storage::snap() {
    storageList.clear();
}

void Storage::add(list<goods>::iterator mygood) {
    goods* good = new goods(mygood->id, mygood->sender, mygood->receiver, mygood->needTime, curDays);
    storageList.push_front(*good);
    storageList.sort();
}

Storage::~Storage() {
    snap();
}


Dispatch::Dispatch() {
    curDays = 0;
}

void Dispatch::send(int id, string send, string receiver, int arrive_time) {
    goods* good = new goods(id, send, receiver, arrive_time, 0, curDays);
    dispatchList.push_front(*good);
    dispatchList.sort();
}

void Dispatch::show() {
    for(iter = dispatchList.begin(); iter != dispatchList.end(); ++iter){
        cout << iter->id << "," << iter->sender << "," << iter->receiver << "," << iter->needTime + iter->timeArrivedDis - curDays << endl;
    }
}

void Dispatch::snap() {
    dispatchList.clear();
}

Dispatch::~Dispatch() {
    snap();
//    delete dispatchList;              //?????????????????
}

void Dispatch::next_day() {
    curDays++;
    for(iter = dispatchList.begin(); iter != dispatchList.end();) {
        if(curDays - iter->needTime - iter->timeArrivedDis >= 0){
            hasArrived.push_front(*iter);
            iter = dispatchList.erase(iter);
        }else{
            iter++;
        }
    }
}

list<goods> Dispatch::getGood() {
    return this->hasArrived;
}

void Dispatch::kill() {
    hasArrived.clear();
}

