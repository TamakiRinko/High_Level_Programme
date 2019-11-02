#include <iostream>
using namespace std;

// 一个用以描述几何形状的class
class Shape{
public:
    enum ShapeColor { Red, Green, Blue };

    // 所有形状都必须提供一个函数，用来绘制出自己
    virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle: public Shape{
public:
    // 注意，赋予不同的缺省参数值，这真糟糕
    virtual void draw(ShapeColor color = Green) const{
        cout << color << endl;
    }
};

int main(){
    Shape* r = new Rectangle();
    r->draw();
    cout << "hola!" << endl;
}