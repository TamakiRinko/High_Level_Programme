//
// Created by TamakiRinko on 2019/9/27.
//


#include "CainiaoSystem.hpp"

CainiaoSystem::CainiaoSystem() {

}

void CainiaoSystem::next_day() {
    dispatch.next_day();
    storage.next_day();
    goods* temp = dispatch.getGood();
    goods* cur = temp->next;
    while(cur != NULL){
        storage.add(cur);
        cur = cur->next;
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
    storageList = new goods();
    curDays = 0;
}

void Storage::next_day() {
    curDays++;
}

void Storage::receive(int id) {
    goods* cur = storageList->next;
    goods* pre = storageList;
    while(cur != NULL && cur->id <= id){
        if(cur->id == id){
            cout << cur->sender << "," << cur->receiver << endl;
            pre->next = cur->next;
            delete cur;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    cout << "tan90" << endl;
}

void Storage::show() {
    goods* cur = storageList->next;
    while (cur != NULL){
        cout << cur->id << "," << cur->sender << "," << cur->receiver << "," << curDays - cur->timeArrivedSto << endl;
        cur = cur->next;
    }
}

void Storage::snap() {
    goods* cur = storageList->next;
    goods* pre = storageList;
    while(cur != NULL){
        pre = cur->next;
        delete cur;
        cur = pre;
    }
    storageList->next = NULL;
}

void Storage::add(goods* mygood) {
    goods* good = new goods(mygood->id, mygood->sender, mygood->receiver, mygood->needTime, curDays);
    goods* cur = storageList->next;
    goods* pre = storageList;
    while (cur != NULL){
        if(cur->id > mygood->id){
            pre->next = good;
            good->next = cur;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    pre->next = good;
}

Storage::~Storage() {
    snap();
}


Dispatch::Dispatch() {
    dispatchList =  new goods();
    hasArrived = new goods();
    curDays = 0;
}

void Dispatch::send(int id, string send, string receiver, int arrive_time) {
    goods* good = new goods(id, send, receiver, arrive_time, 0, curDays);
    goods* cur = dispatchList->next;
    goods* pre = dispatchList;
    while (cur != NULL){
        if(cur->id > id){
            pre->next = good;
            good->next = cur;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    pre->next = good;
}

void Dispatch::show() {
    goods* cur = dispatchList->next;
    while (cur != NULL){
        cout << cur->id << "," << cur->sender << "," << cur->receiver << "," << cur->needTime + cur->timeArrivedDis - curDays << endl;
        cur = cur->next;
    }
}

void Dispatch::snap() {
    goods* cur = dispatchList->next;
    goods* pre = dispatchList;
    while(cur != NULL){
        pre = cur->next;
        delete cur;
        cur = pre;
    }
    dispatchList->next = NULL;
}

Dispatch::~Dispatch() {
    snap();
//    delete dispatchList;              //?????????????????
}

void Dispatch::next_day() {
    curDays++;
    goods* cur = dispatchList->next;
    goods* pre = dispatchList;
    while(cur != NULL){
        if(curDays - cur->needTime - cur->timeArrivedDis >= 0){
            pre->next = cur->next;
            cur->next = hasArrived->next;
            hasArrived->next = cur;
            cur = pre;
        }
        pre = cur;
        cur = cur->next;
    }
}

goods* Dispatch::getGood() {
    return this->hasArrived;
}

void Dispatch::kill() {
    goods* cur = hasArrived->next;
    goods* pre = hasArrived;
    while(cur != NULL){
        pre = cur->next;
        delete cur;
        cur = pre;
    }
    hasArrived->next = NULL;
}

