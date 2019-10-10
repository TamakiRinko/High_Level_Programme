#include<iostream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

class CircleWithFixedSize {
private:
    int x;
    int y;
    int radius;
    static int size;
public:
    CircleWithFixedSize(int x, int y){
        this->x = x;
        this->y = y;
        this->radius = size;
    }
    CircleWithFixedSize& operator=(const CircleWithFixedSize& circle);      //赋值
    static void changeSize(int s){
        size = s;
    }
    void show(){
        cout << x << ", " << y << ", " << radius << endl;
    }
};
int CircleWithFixedSize::size = 5;

CircleWithFixedSize& CircleWithFixedSize::operator=(const CircleWithFixedSize& circle){
    this->x = circle.x;
    this->y = circle.y;
    this->radius = circle.radius;
    return *this;
}

int main(int argc, char const *argv[]){
    CircleWithFixedSize c1 = CircleWithFixedSize(1, 1); //圆心的坐标为(1, 1), 半径为一个给定值（比如5）
    CircleWithFixedSize c2 = CircleWithFixedSize(2, 2); //圆心的坐标为(2, 2), 半径为一个给定值（比如5）
    // 进行一些操作，改变后续定义该类的对象的半径
    CircleWithFixedSize::changeSize(10);
    CircleWithFixedSize c3 = CircleWithFixedSize(1, 3); //圆心的坐标为(1, 3), 半径为另一个给定值（比如10）
    CircleWithFixedSize c4 = CircleWithFixedSize(1, 3); //圆心的坐标为(1, 3), 半径为另一个给定值（比如10）
    // 进行一些操作，再次改变后续定义该类的对象的半径
    CircleWithFixedSize::changeSize(15);
    CircleWithFixedSize c5 = CircleWithFixedSize(2, 3); //圆心的坐标为(2, 3), 半径为另一个给定值（比如15）
    c1.show();
    c2.show();
    c3.show();
    c4.show();
    c5.show();

    return 0;
}