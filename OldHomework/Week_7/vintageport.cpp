#include "vintageport.h"

VintagePort::VintagePort(): Port("none", "vintage", 0){
    nickname = new char[5];
    strcpy(nickname, "none");
    year = 0;
}

VintagePort::VintagePort(const char* br, int b, const char* nn, int y): Port(br, "vintage", b){
    nickname = new char[strlen(nn) + 1];
    strcpy(nickname, nn);
    year = y;
}

VintagePort::VintagePort(const VintagePort& vp): Port(vp){//需要在自定义的拷贝构造函数的“成员初始化表”中显示指出
    delete[] nickname;
    nickname = new char[strlen(vp.nickname) + 1];
    strcpy(nickname, vp.nickname);
    year = vp.year;
}

VintagePort& VintagePort::operator = (const VintagePort& vp){//需要在自定义的赋值操作符重载函数中显示指出
    if(this == &vp) return *this;
    *(Port*)this = vp;//or this->Port::operator = (vp);
    delete[] nickname;
    nickname = new char[strlen(vp.nickname) + 1];
    strcpy(nickname, vp.nickname);
    year = vp.year;
    return *this;
}

void VintagePort::Show() const{
    this->Port::Show();
    cout << "Nickname: " << nickname << endl
         << "year: " << year << endl; 
}

ostream& operator << (ostream& os, const VintagePort& vp){
    os << *(Port*)(&vp) << ", ";//输出Port部分
    os << vp.nickname << ", " << vp.year;
    return os;
}