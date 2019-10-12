#include "ParkingLotUser.h"

int main() {
    ParkingLotUser users[19];
    int status_id = -1;
    // 首先占用其中的 19 个车位 : 1,2,...,18,19
    for(int i =0;i< 19;i++)
        status_id = users[i].tryEnter();
    ParkingLotUser amy;
    ParkingLotUser bob;
    // amy 申请到 20 号车位
    amy.tryEnter();
    cout << amy.getStatus() << endl;
    // 车位已满,bob 进入等待队列
    bob.tryEnter();
    cout << bob.getStatus() << endl;
    // amy 离开,释放出 20 号车位
    // 系统自动将 20 号车位分配给等待队列中的 bob
    amy.leave();
    cout << amy.getStatus() << endl;
    cout << bob.getStatus() << endl;
    return 0;
}