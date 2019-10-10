#include "Money.h"

Money operator+(const Money& m1, const Money& m2){
    int flag = 1;
    int num1 = m1.y * 100 + m1.j * 10 + m1.f;
    int num2 = m2.y * 100 + m2.j * 10 + m2.f;
    int sum = num1 + num2;
    if(sum < 0){
        sum = -sum;
        flag = -1;
    }
    int y = sum / 100;
    int j = sum / 10 - 10 * y;
    int f = sum - 10 * j - 100 * y;
    if(flag == -1){
        cout << "和：-" << y << "元" << j << "角" << f << "分" << endl;
    }else{
        cout << "和：" << y << "元" << j << "角" << f << "分" << endl;        
    }
    y = y * flag;
    Money m3(y, j, f);
    return m3;
}

Money operator-(const Money& m1, const Money& m2){
    int flag = 1;
    int num1 = m1.y * 100 + m1.j * 10 + m1.f;
    int num2 = m2.y * 100 + m2.j * 10 + m2.f;
    int minus = num1 - num2;
    if(minus < 0){
        minus = -minus;
        flag = -1;
    }
    int y = minus / 100;
    int j = minus / 10 - 10 * y;
    int f = minus - 10 * j - 100 * y;
    if(flag == -1){
        cout << "差：-" << y << "元" << j << "角" << f << "分" << endl;
    }else{
        cout << "差：" << y << "元" << j << "角" << f << "分" << endl;        
    }
    y = y * flag;
    Money m3(y, j, f);
    return m3;
}

int main(int argc, char const *argv[]){
    int y1, j1, f1;
    int y2, j2, f2;
    cout << "请输入元、角、分：\n";
    cin >> y1 >> j1 >> f1;
    cout << "请输入元、角、分：\n";
    cin >> y2 >> j2 >> f2;
    Money m1(y1, j1, f1);
    Money m2(y2, j2, f2);
    m1 + m2;
    m1 - m2;
    return 0;
}