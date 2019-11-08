#include "OpSeq.h"

int main() {
    OpSeq seq("init . reverse . add 1");
    int a[3] = {2,5,3};
    List x(a,3);
    List ret(nullptr,0);
    ret = seq.forward_computing(x);
    ret.show();
    cout << seq.gather_value() << endl;
    ret = seq.backward_computing(x);
    ret.show();
    cout << seq.gather_value() << endl;
    return 0;
}