#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>

using namespace std;

class MyException: public exception{
private:
    string msg;
public:
    MyException(string m){
        msg = m;
    }
    ~MyException() throw (){}

    const char* what() const throw (){
        return msg.c_str();
    }

    // void what(){
    //     cout << msg << endl;
    // }
};


class User{
private:
    char uID[11]; // 用户ID
    char uPwd[16]; // 用户密码
    
public:
    User(){}
    void createUsers(const char* id, const char* pwd); //创建用户
    void verifyUsers(); //验证用户
};

void User::createUsers(const char* id, const char* pwd){
    try{
        if(strlen(id) > 10){
            throw MyException("ID不合法，长度不合法!");
        }
        if((id[0] > 'Z' || id[0] < 'A') && id[0] != '_'){
            throw MyException("ID不合法，首字母不合法!");
        }
        if(strlen(pwd) >= 16 || strlen(pwd) < 6){
            throw MyException("PWD不合法，长度不合法!");
        }
        string pwd1(pwd);
        string pwd2(pwd);
        string pwd3(pwd);
        transform(pwd1.begin(), pwd1.end(), pwd2.begin(), ::toupper);
        transform(pwd1.begin(), pwd1.end(), pwd3.begin(), ::tolower);
        if(pwd1 == pwd2 || pwd1 == pwd3){
            throw MyException("PWD不合法，大小写不合法!");
        }
        strcpy(uID, id);
        strcpy(uPwd, pwd);
        cout << "ID, PWD均合法!" << endl;

        ofstream fout;
        fout.open("user.dat", ios::app | ios::out | ios::binary);
        if(!fout.is_open()){
            throw MyException("文件打开错误!");
        }
        fout.write((char*)this, sizeof(*this));
        cout << "用户存储成功!" << endl;
    }
    catch(const std::exception& e){
        cerr << e.what() << '\n';
    }
    
}

void User::verifyUsers(){
    
}

int main(int argc, char const *argv[]){
    User user;
    user.createUsers("Hosasssla", "sssssasSsaswds");
    return 0;
}
