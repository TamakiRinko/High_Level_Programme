#include "CainiaoSystem.hpp"

int main() {
    CainiaoSystem sys;
// day 0
    sys.send(10000000, "Thor", "Thanos", 1);
    sys.send(10000001, "Thanos", "Thor", 3);
    sys.next_day();
// day 1
    sys.send(10000002, "Captain America", "Thor", 4);
    sys.send(10000003, "Thanos", "Thor", 1);
    sys.receive(10000002); // "tan90"
    sys.receive(10000000); // "Thor,Thanos"
    sys.next_day();
// day 2
    sys.receive(10000001); // "tan90"
    sys.next_day();
// day 3
    sys.receive(10000001); // "Thanos,Thor"
    sys.receive(10000003); // "Thanos,Thor"
    sys.next_day();
    sys.next_day();
// snap
    sys.show_storage();
    sys.show_dispatch();
    sys.snap();
    sys.show_storage();
    sys.show_dispatch();
    return 0;
}