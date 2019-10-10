#include "Rectangle.h"

Rectangle::Rectangle(){}

Rectangle::Rectangle(int w, int h){
    this->height = h;
    this->width = w;
}

void Rectangle::setWH(int w, int h){
    this->height = h;
    this->width = w;
}

int Rectangle::CRectangle(){
    return (this->height + this->width) * 2;
}

int main(){
    Rectangle rectangle(3, 4);
    cout << "The perimeter of the rectangle is: " << rectangle.CRectangle() << endl;
    rectangle.setWH(5, 6);
    cout << "The perimeter of the rectangle is: " << rectangle.CRectangle() << endl;
    return 0;
}
