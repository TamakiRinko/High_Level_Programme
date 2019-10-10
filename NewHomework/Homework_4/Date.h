#include<iostream>
#include<time.h>
using namespace std;
class Date {
private:
    int year;
    int month;
    int day;
    time_t msFrom1900;
public:
    Date(int year, int month, int day){
        this->year = year;
        this->month = month;
        this->day = day;
        tm myTime = {0};
        myTime.tm_year = year - 1900;
        myTime.tm_mon = month - 1;
        myTime.tm_mday = day;
        this->msFrom1900 = mktime(&myTime);
    }
    void display();
    friend const Date operator++(Date& date, int x);
};