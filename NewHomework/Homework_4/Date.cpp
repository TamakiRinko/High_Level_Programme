#include "Date.h"
void Date::display(){
    cout<< year <<"-"<< month <<"-"<< day <<endl;
}

const Date operator++(Date& date,int x){
    date.msFrom1900 += 86400;
    tm *myTm = localtime(&date.msFrom1900);
    date.year = myTm->tm_year + 1900;
    date.month = myTm->tm_mon + 1;
    date.day = myTm->tm_mday;
}

int main(){
    // cout << "请输入年、月、日：\n";
    // int year, month, day;
    // cin >> year >> month >> day;
    // Date d1(year, month, day);
    // cout<<"今天是：";
    // d1.display();
    // d1++;
    // cout<<"明天是：";
    // d1.display();
    cout << -139 / 10 << endl;
    return 0;
}