//
// Created by TamakiRinko on 2019/9/14.
//

#include "GoodsList.h"

Goods::Goods(string name, int nums){
    this->name = name;
    this->nums = nums;
}

void Goods::show(){
    cout << this->name << "," << this->nums;
}

Goods::~Goods(){
    ;
}

GoodsList::GoodsList(){
    Node* node = new Node();
    node->goods = NULL;
    node->next = NULL;
    list = node;
}

int GoodsList::count(){
    int num = 0;
    Node* cur = list->next;
    while (cur != NULL){
        num++;
        cur = cur->next;
    }
    return num;
}

void GoodsList::insert(Goods* goods){
    Node* cur = list->next;
    Node* pre = list;
    while (cur != NULL){
        if (cur->goods->getName() == goods->getName()){
            cur->goods->increaseNum(goods->getNum());
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    Node* temp = new Node();
    Goods* good1 = new Goods(goods->getName(), goods->getNum());
    temp->goods = good1;
    temp->next = NULL;
    pre->next = temp;
    return;
}

void GoodsList::remove(string name, int nums){
    Node* cur = list->next;
    Node* pre = list;
    while (cur != NULL){
        if (cur->goods->getName() == name){
            if (cur->goods->getNum() >= nums){
                cur->goods->decreaseNum(nums);
            }
            else{
                cout << "Not enough goods!\n";
                return;
            }
            if (cur->goods->getNum() == 0){
                pre->next = cur->next;
                delete cur;
                return;
            }else if(cur->goods->getNum() > 0){
                return;
            }
        }
        pre = cur;
        cur = cur->next;
    }
    cout << "Not enough goods!\n";  //没有该商品
    return;
}

void GoodsList::show(){
    Node* cur = list->next;
    while (cur != NULL && cur->next != NULL){
        cur->goods->show();
        cout << " ";
        cur = cur->next;
    }
    if (cur != NULL){
        cur->goods->show();
        cout << endl;
    }
}

/**
 * 选择法排序
 */
void GoodsList::sort(){
    Node* tempHead = new Node();  //新链表的头部，不可用之前的头部！
    tempHead->goods = NULL;
    tempHead->next = NULL;
    if(list->next == NULL){
        return;
    }
    Node* temp = tempHead;
    int num = count();
    for (int i = 0; i < num; ++i) {
        Node* max = list;
        Node* cur = list->next;
        Node* preMax = list;    //当前最大的一个值的前一个
        Node* pre = list;
        int maxNum = 0;
        while(cur != NULL){
            if(cur->goods->getNum() >= maxNum){
                preMax = pre;
                max = cur;
                maxNum = cur->goods->getNum();
            }
            pre = cur;
            cur = cur->next;
        }
        temp->next = max;
        temp = temp->next;
        preMax->next = max->next;
        max->next = NULL;
    }
    delete list;
    list = tempHead;
}

void GoodsList::clear(){
    Node* cur = list->next;
    while (cur != NULL){
        list->next = cur->next;
        delete cur;
        cur = list->next;
    }
    list->next = NULL;
}

GoodsList::~GoodsList(){
    delete list;
}
