#include <string>
#include <iostream>
#include <list>
using namespace std;

struct goods{
    int id;
    string sender;
    string receiver;
    int needTime;
    int timeArrivedSto;
    int timeArrivedDis;
    goods* next;
    goods(){
        next = NULL;
        id = 0;
        sender = "";
        receiver = "";
        needTime = 0;
        timeArrivedSto = 0;
        timeArrivedDis = 0;
    }
    goods(int ids, string senders, string receivers, int arrive_times, int timeArrivedStos = 0, int timeArrivedDiss = 0){
        id = ids;
        sender = senders;
        receiver = receivers;
        needTime = arrive_times;
        timeArrivedSto = timeArrivedStos;
        timeArrivedDis = timeArrivedDiss;
        next = NULL;
    }
    bool operator<(goods& b){
        return id<b.id;
    }
};

class Dispatch {

private:
    list<goods> dispatchList;
    list<goods> hasArrived;
    list<goods>::iterator iter;
    int curDays;
  // 自行设计货物以及其他辅助变量以何种形式存储
public:
  Dispatch();
  void next_day(); // 需要维护一个当前时间戳
  // 在运送系统添加货物
  void send(int id,
            string send,
            string receiver,
            int arrive_time);

  // 以id从小到大的顺序输出所有剩余货物的
  // id，发件人，收件人，及还有几天到达，
  // 没有就不输出(当天为0天)
  void show();

  // 销毁所有货物
  void snap();

  list<goods> getGood();

  void kill();

  ~Dispatch();
};

class Storage {

private:
    list<goods> storageList;
    list<goods>::iterator iter;
    int curDays;
  // 自行设计货物以及其他辅助变量以何种形式存储
public:
  Storage();
  void next_day();

  // 如果该id对应的货物不在仓库里，则输出"tan90"。
  // 如果存在，则输出输出"寄件人名字,收件人名字"，并从系统中删除该货物
  void receive(int id);

  void add(list<goods>::iterator mygood);

  // 以id从小到大的顺序输出所有剩余货物的
  // id，发件人，收件人，以及已经到达了几天，
  // 没有就不输出(当天为0天)
  void show();

  // 销毁所有货物
  void snap();

  ~Storage();
};

class CainiaoSystem {

private:
  Storage storage;
  Dispatch dispatch;
  list<goods>::iterator iter;


public:
  CainiaoSystem();
  void next_day();
  // 调用storage和dispacth的tomorrow方法，
  // 然后将当天到达的货物从dispatch转移到storage。
  // 货物如何在二者之间交接需自行设计

  void receive(int id); // 调用storage的receive方法。
  void snap(); // 调用storage和dispatch的snap方法。
  void show_storage();
  void show_dispatch();
  void send(int id,
            string sender,
            string receiver,
            int arrive_time); // 调用dispatch的send方法。
  ~CainiaoSystem();
};
