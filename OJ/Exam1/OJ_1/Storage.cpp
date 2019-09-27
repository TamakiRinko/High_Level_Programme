////
//// Created by TamakiRinko on 2019/9/27.
////
//
//#include "CainiaoSystem.hpp"
//
//Storage::Storage() {
//    storageList = new goods();
//    curDays = 0;
//}
//
//void Storage::next_day() {
//    curDays++;
//}
//
//bool Storage::receive(int id) {
//    goods* cur = storageList->next;
//    goods* pre = storageList;
//    while(cur != NULL && cur->id <= id){
//        if(cur->id == id){
//            cout << cur->sender << "," << cur->receiver << endl;
//            pre->next = cur->next;
//            delete cur;
//            return true;
//        }
//        pre = cur;
//        cur = cur->next;
//    }
//    return false;
//}
//
//void Storage::show() {
//    goods* cur = storageList->next;
//    while (cur != NULL){
//        cout << cur->id << ", " << cur->sender << ", " << cur->receiver << ", " << curDays - cur->timeArrivedSto << endl;
//        cur = cur->next;
//    }
//}
//
//void Storage::snap() {
//    goods* cur = storageList->next;
//    goods* pre = storageList;
//    while(cur != NULL){
//        pre = cur->next;
//        delete cur;
//        cur = pre;
//    }
//    storageList->next = NULL;
//}
//
//void Storage::add(goods* mygood) {
//    goods* good = new goods(mygood->id, mygood->sender, mygood->receiver, mygood->needTime, curDays);
//    goods* cur = storageList->next;
//    goods* pre = storageList;
//    while (cur != NULL){
//        if(cur->id > mygood->id){
//            pre->next = good;
//            good->next = cur;
//            return;
//        }
//        pre = cur;
//        cur = cur->next;
//    }
//    if(cur == NULL){            //到达末尾
//        pre->next = good;
//    }
//}
//
//Storage::~Storage() {
//    snap();
//}
//
