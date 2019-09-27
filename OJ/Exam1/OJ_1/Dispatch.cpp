////
//// Created by TamakiRinko on 2019/9/27.
////
//
//#include "CainiaoSystem.hpp"
//
//Dispatch::Dispatch() {
//    dispatchList =  new goods();
//    hasArrived = new goods();
//    curDays = 0;
//}
//
//void Dispatch::send(int id, string send, string receiver, int arrive_time) {
//    goods* good = new goods(id, send, receiver, arrive_time, 0, curDays);
//    goods* cur = dispatchList->next;
//    goods* pre = dispatchList;
//    while (cur != NULL){
//        if(cur->id > id){
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
//void Dispatch::show() {
//    goods* cur = dispatchList->next;
//    while (cur != NULL){
//        cout << cur->id << ", " << cur->sender << ", " << cur->receiver << ", " << cur->needTime + cur->timeArrivedDis - curDays << endl;
//        cur = cur->next;
//    }
//}
//
//void Dispatch::snap() {
//    goods* cur = dispatchList->next;
//    goods* pre = dispatchList;
//    while(cur != NULL){
//        pre = cur->next;
//        delete cur;
//        cur = pre;
//    }
//    dispatchList->next = NULL;
//}
//
//Dispatch::~Dispatch() {
//    snap();
////    delete dispatchList;              //?????????????????
//}
//
//void Dispatch::next_day() {
//    curDays++;
//    goods* cur = dispatchList->next;
//    goods* pre = dispatchList;
//    while(cur != NULL){
//        if(curDays - cur->needTime - cur->timeArrivedDis >= 0){
//            pre->next = cur->next;
//            cur->next = hasArrived->next;
//            hasArrived->next = cur;
//            cur = pre;
//        }
//        pre = cur;
//        cur = cur->next;
//    }
//}
//
//goods* Dispatch::getGood() {
//    return this->hasArrived;
//}
//
//void Dispatch::kill() {
//    goods* cur = hasArrived->next;
//    goods* pre = hasArrived;
//    while(cur != NULL){
//        pre = cur->next;
//        delete cur;
//        cur = pre;
//    }
//    hasArrived->next = NULL;
//}
//
