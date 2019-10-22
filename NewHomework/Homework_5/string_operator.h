#include <iostream>
#include <string.h>
using namespace std;

class CustomString{
public:
    //构造函数
    CustomString();
    CustomString(const char* str);
    CustomString(CustomString& c);                                  //拷贝构造
    //析构函数
    ~CustomString();
    //成员函数重载
    char& operator [] (int i);
    CustomString& operator = (const CustomString& c);               //赋值构造
    CustomString& operator += (CustomString& c);

    //友元重载
    friend ostream& operator << (ostream& out, CustomString& c);
    friend istream& operator >> (istream& in, CustomString& c);
    friend CustomString& operator + (CustomString& c1, CustomString& c2);
    friend bool operator == (CustomString& c1, CustomString& c2);
    friend bool operator != (CustomString& c1, CustomString& c2);
private:
    char* p; // 字符串的起始地址
    int len; // 字符串的长度
};