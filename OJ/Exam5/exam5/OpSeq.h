//
// Created by rinko on 2019/11/8.
//

#ifndef EXAM5_OPSEQ_H
#define EXAM5_OPSEQ_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class List{
    vector<int> list;
    int len;
public:
    List(int* a,int len);
    void show();

    List& operator=(List x);

    int getLen();

    void add(int n);
    void reverse();
    void init();
    void tail();
    bool isEmpty(){
        return len == 0;
    }
};

class OpSeq {
    vector<string> opList;
    int value;
public:
    OpSeq(){
        value = 0;
    }
    OpSeq(string s);
    OpSeq(OpSeq& opSeq);
    List forward_computing(List input);
    List backward_computing(List input);
    int gather_value();
};


#endif //EXAM5_OPSEQ_H
