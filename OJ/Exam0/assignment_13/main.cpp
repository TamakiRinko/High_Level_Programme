#include "GoodsList.h"

int main()
{
    GoodsList list;
    cout << list.count() << endl;
    list.remove("apple", 10);
    list.sort();
    list.remove("peach", 20);
    list.remove("peach", 20);
    list.remove("peach", 20);
    list.clear();
    cout << list.count() << endl;
    Goods* good1 = new Goods("apple", 500);
    Goods* good2 = new Goods("pear", 100);
    Goods* good3 = new Goods("peach", 150);
    Goods* good4 = new Goods("peach", 450);
    Goods* good5 = new Goods("pineapple", 100);
    list.insert(good1);
    list.insert(good2);
    list.insert(good3);
    list.insert(good4);
    list.insert(good5);
    list.show();
    list.remove("apple", 4900);
    list.sort();
    list.show();
    list.remove("peach", 500);
    list.insert(good3);
    list.sort();
    list.show();
    cout << list.count() << endl;
    list.clear();
    cout << list.count() << endl;
    list.sort();
    list.show();
}