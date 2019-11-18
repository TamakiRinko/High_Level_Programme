#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

int main(int argc, char const *argv[]){
    fstream file;
    file.open("test1.txt", ios::in);
    string str;
    file >> str;
    while(!file.fail()){
        cout << str << endl;
        file >> str;
    } 
    file.close();
    file.open("test2.txt", ios::in);
    file >> str;
    while(!file.fail()){
        cout << str << endl;
        file >> str;
    }
    return 0;
}