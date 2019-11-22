#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define print(x) cout << x << endl
#define input(x) cin >> x

int main(int argc, char const *argv[]){
    ifstream fin1, fin2;
    ofstream fout;
    fin1.open("test1.txt", ios::in);
    fin2.open("test2.txt", ios::in);
    fout.open("result.txt", ios::out);

    if(!fin1.is_open() || !fin2.is_open() || !fout.is_open()){
        cerr << "open error!\n";
        return 0;
    }

    string str1, str2, result;
    getline(fin1, str1);
    getline(fin2, str2);
    while (!fin1.fail() && !fin2.fail()){           //读入最小长度
        result = result + str1 + " " + str2 + "\n";
        getline(fin1, str1);
        getline(fin2, str2);
    }
    while (!fin1.fail()){                           //fin1可能未读完
        result = result + str1 + "\n";
        getline(fin1, str1);
    }
    while(!fin2.fail()){                            //fin2可能未读完
        result = result + str2 + "\n";
        getline(fin2, str2);
    }
    fin1.close();
    fin2.close();
    fout << result;
    fout.close();
    
    return 0;
}