#include<iostream>
#include<string>
using namespace std;

class ChairMan {
private:
    string name;
    int age;
    string subject;
    ChairMan(string name, int age, string subject){     //构造
        this->name = name;
        this->age = age;
        this->subject = subject;
    }
    ChairMan(const ChairMan&);                          //拷贝
    ChairMan& operator=(const ChairMan&);               //赋值
public:
    static ChairMan& getInstance(string name, int age, string subject){
        static ChairMan chairMan(name, age, subject);
        return chairMan;
    }
    void show(){
        cout << "name: " << name << ", age: " << age << ", subject: " << subject << endl;
    }
};

#define print(x) cout << x << endl
#define input(x) cin >> x

int main(int argc, char const *argv[]){
    // ChairMan chairMan = new ChairMan();              //error，构造函数私有
    // ChairMan chairMan = ChairMan::getInstance();     //error，赋值函数私有
    // ChairMan chairMan(ChairMan::getInstance());      //error，拷贝构造函数私有
    ChairMan& chairMan = ChairMan::getInstance("David", 21, "Computer Science");
    chairMan.show();

    return 0;
}