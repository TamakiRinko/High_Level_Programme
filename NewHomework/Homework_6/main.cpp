#include "Polygon.h"
#include "Engine.h"

int main(){
    // Rectangle r(10, 20);
    // cout << r.area() << endl;
    // Triangle t(3, 4, 5);
    // cout << t.area() << " " << t.primeter() << endl;
    // Trapezoid tt(3, 6, 3, 3);
    // cout << tt.area() << " " << tt.primeter() << endl;
    // Polygon* p = new Rectangle(3, 4);
    // cout << p->area() << " " << p->primeter() << endl;
    AdvancedMotorEngine a(20, NORMAL);
    a.addoil(50);
    cout << a.display() << endl;
    cout << a.checkoil() << endl;
    a.addoil(50);
    cout << a.display() << endl;
    cout << a.checkoil() << endl;
}