#include"string_operator.h"

//析构函数
CustomString::~CustomString(){
    delete[] p;
    p = NULL;
}

CustomString::CustomString(){           //初始为空，长度为1
    p = new char[1];
    len = 1;
    p[0] = '\0';
}

CustomString::CustomString(const char* str){
    len = strlen(str);
    p = new char[len + 1];
    strcpy(p, str);
}

CustomString::CustomString(CustomString& c){
    len = c.len;
    p = new char[len + 1];
    strcpy(p, c.p);
}

//成员函数重载
char& CustomString::operator [] (int i){
    return p[i];
}

CustomString& CustomString::operator = (const CustomString& c){         //const
    delete[] p;
    len = c.len;
    p = new char[len + 1];
    strcpy(p, c.p);
    return *this;
}

CustomString& CustomString::operator += (CustomString& c){           //返回自身，可迭代执行
    string str1(p);
    string str2(c.p);
    str1 = str1 + str2;
    len = str1.length();
    delete[] p;
    p = new char[len + 1];
    strcpy(p, str1.c_str());
    return *this;
}


//友元重载
ostream& operator << (ostream& out, CustomString& c){
    out << c.p;
    return out;
}

istream& operator >> (istream& in, CustomString& c){
    in >> c.p;
    c.len = strlen(c.p);
    return in;
}

CustomString& operator + (CustomString& c1, CustomString& c2){              //返回引用！否则a+b临时变量无法被引用
    string str1(c1.p);
    string str2(c2.p);
    string str3 = str1 + str2;
    CustomString* c = new CustomString(str3.c_str());
    return *c;
}

bool operator == (CustomString& c1, CustomString& c2){
    return (c1.len == c2.len && !strcmp(c1.p, c2.p));
}

bool operator != (CustomString& c1, CustomString& c2){
    return (c1.len != c2.len || strcmp(c1.p, c2.p));
}

int main(){
    CustomString mystr("this is e CustomString class for testing!");
    cout << mystr[8] << endl;
    mystr[8] = 'a';
    cout << mystr <<endl;
    CustomString mystr2 = mystr;
    cout << mystr2 << endl;
    CustomString mystr3;
    mystr3 = mystr + mystr2;
    cout << mystr + mystr2 << endl;
    mystr3 += mystr;
    cout << mystr3 << endl;
    cout << (mystr != mystr2) << endl;
    cout << (mystr == mystr3) << endl;
    CustomString mystr4;
    cout << "Input any string to test the overloaded input operator >>: " << endl;
    cin >> mystr4;
    cout << mystr4 << endl;
    cout << "Congratulations! testing passed!" << endl;
    return 0;
}