#include<iostream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

class Component {
private:
    int Weight;
public:
    static int TotalWeights;
    Component(int w){
        Weight = w;
        TotalWeights += w;  //增加该零件的重量
    }
    int GetWeights(){
        return this->Weight;
    }
};
int Component::TotalWeights = 0;

int main(int argc, char const *argv[]){
    int a, b;
    cin>>a>>b;
    Component A(a);
    Component B(b);
    cout<<B.TotalWeights<<endl;
    return 0;
}