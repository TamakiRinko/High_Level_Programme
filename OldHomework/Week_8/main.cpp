#include "amphibiancar.h"

int main(){
    car c(3, 210);
    c.drive();
    Boat b(5, 2.12);
    b.dirve();
    AmphibianCar a(4, 200, 1.35, true);
    a.dirve();
    a.showMembers();
    a.setWeight(3);
    a.setFlag(false);
    a.dirve();
    a.showMembers();
    return 0;
}