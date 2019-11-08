//
// Created by rinko on 2019/11/8.
//

#include "OpSeq.h"

OpSeq::OpSeq(string s) {
    value = 0;
    if(s == ""){
        return;
    }
    int preIndex = 0;
    int length = s.length();
    for(int i = 0; i < length - 2; ++i){
        if(s[i] == ' ' && s[i + 1] == '.' && s[i + 2] == ' '){
            string temp = s.substr(preIndex, i - preIndex);
            preIndex = i + 3;
            i = i + 2;
            opList.push_back(temp);
        }
    }
    string temp = s.substr(preIndex);
    opList.push_back(temp);
}

OpSeq::OpSeq(OpSeq &opSeq) {
    value = opSeq.value;
    for(int i = 0; i < opSeq.opList.size(); ++i){
        opList.push_back(opSeq.opList[i]);
    }
}

List OpSeq::forward_computing(List input) {
    if(input.isEmpty()){
        return input;
    }
    for(int i = opList.size() - 1; i >= 0; --i){
        if(input.isEmpty()){
            return input;
        }
        if(opList[i][0] == 'i'){
            value += input.getLen();
            input.init();
        }else if(opList[i][0] == 't'){
            value += input.getLen();
            input.tail();
        }else if(opList[i][0] == 'r'){
            value += input.getLen();
            input.reverse();
        }else if(opList[i][0] == 'a'){
            value += input.getLen();
            string temp = opList[i].substr(4, opList[i].size() - 3);
            int n = atoi(temp.c_str());
            input.add(n);
        }
    }

    return input;
}

List OpSeq::backward_computing(List input) {
    if(input.isEmpty()){
        return input;
    }
    for(int i = 0; i < opList.size(); ++i){
        if(input.isEmpty()){
            return input;
        }
        if(opList[i][0] == 'i'){
            value += input.getLen();
            input.init();
        }else if(opList[i][0] == 't'){
            value += input.getLen();
            input.tail();
        }else if(opList[i][0] == 'r'){
            value += input.getLen();
            input.reverse();
        }else if(opList[i][0] == 'a'){
            value += input.getLen();
            string temp = opList[i].substr(4, opList[i].size() - 3);
            int n = atoi(temp.c_str());
            input.add(n);
        }
    }

    return input;
}

int OpSeq::gather_value() {
    return value;
}

List::List(int *a, int len) {
    if(len == 0){
        this->len = 0;
        return;
    }
    this->len = len;
    for(int i = 0; i < len; ++i){
        list.push_back(a[i]);
    }
}

void List::show() {
    if(len == 0){
        cout << "EmptyList" << endl;
        return;
    }
    for(int i = 0; i < len - 1; ++i){
        cout << list[i] << " ";
    }
    cout << list[len - 1] << endl;
}

List& List::operator=(List x) {
    list.clear();
    len = 0;
    for(int i = 0; i < x.list.size(); ++i){
        list.push_back(x.list[i]);
    }
    len = x.len;
}

int List::getLen(){
    return len;
}

void List::add(int n){
    for(int i = 0; i < len; ++i){
        list[i] = list[i] + n;
    }
}
void List::reverse(){
    std::reverse(list.begin(), list.end());
}
void List::init(){
    list.pop_back();
    len--;
}
void List::tail(){
    std::reverse(list.begin(), list.end());
    list.pop_back();
    std::reverse(list.begin(), list.end());
    len--;
}


