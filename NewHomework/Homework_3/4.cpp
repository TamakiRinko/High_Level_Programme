#include<iostream>
#include<string>
using namespace std;
class Lion;
class Tiger;
int totalWeights(const Lion& L, const Tiger& T);

class Lion {
private:
    int weight;
public:
    Lion(int w){
        weight = w;
    }
    friend int totalWeights(const Lion& L, const Tiger& T);     //友元函数声明
};

class Tiger {
private:
    int weight;
public:
    Tiger(int w){
        weight = w;
    }
    friend int totalWeights(const Lion& L, const Tiger& T);     //友元函数声明
};

int main(int argc, char const *argv[]){
    int w1, w2;
    cin>>w1>>w2;
    Lion L(w1);
    Tiger T(w2);
    cout<<totalWeights(L, T)<<endl;
    return 0;
}

int totalWeights(const Lion& L, const Tiger& T){
    return L.weight + T.weight;
}