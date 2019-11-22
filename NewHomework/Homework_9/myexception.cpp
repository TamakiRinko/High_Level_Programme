#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>

using namespace std;

class MyException: public exception{            //继承exceptions类
private:
    string msg;
public:
    MyException(string m){
        msg = m;
    }
    ~MyException() throw (){}                   //throw()表示承诺函数不会抛出异常

    const char* what() const throw (){
        return msg.c_str();
    }
};


class User{
private:
    char uID[11]; // 用户ID
    char uPwd[16]; // 用户密码
    
public:
    User(){}
    void createUsers(const char* id, const char* pwd);          //创建用户
    void verifyUsers(const char* id, const char* pwd);          //验证用户
    bool verify(const char* id, const char* pwd);   //文件验证
};

void User::createUsers(const char* id, const char* pwd){
    try{
        if(verify(id, pwd)){
            throw MyException("已有该用户，无法注册!");
        }
    }catch(const exception& e){
        if(strcmp(e.what(), "已有该用户，无法注册!") == 0){          //只抛出无法注册的异常
            cerr << e.what() << '\n';
            return;
        }
    }

    try{
        if(strlen(id) > 10){                                //ID长度不合法
            throw MyException("ID不合法，长度不合法!");
        }
        if((id[0] > 'Z' || id[0] < 'A') && id[0] != '_'){   //ID首字母不合法
            throw MyException("ID不合法，首字母不合法!");
        }
        if(strlen(pwd) >= 16 || strlen(pwd) < 6){           //密码长度不合法
            throw MyException("PWD不合法，长度不合法!");
        }
        string pwd1(pwd);
        string pwd2(pwd);
        string pwd3(pwd);
        transform(pwd1.begin(), pwd1.end(), pwd2.begin(), ::toupper);   //转为全大写
        transform(pwd1.begin(), pwd1.end(), pwd3.begin(), ::tolower);   //转为全小写
        if(pwd1 == pwd2 || pwd1 == pwd3){                               //PWD大小写不合法
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
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    
}

void User::verifyUsers(const char* id, const char* pwd){
    try{
        if(strlen(id) == 0){
            throw MyException("未输入用户名!");
        }else if(strlen(pwd) == 0){
            throw MyException("未输入密码!");
        }
        if(verify(id, pwd)){
            cout << "验证通过!" << endl;
        }
    }catch(const exception& e){
        cerr << e.what() << '\n';
    }
    return;
}

bool User::verify(const char* id, const char* pwd){
    ifstream fin;
    fin.open("user.dat", ios::in | ios::binary);
    if(!fin.is_open()){
        throw MyException("文件打开错误!");
    }

    bool idFlag = false;                                        //是否有该用户
    User user;
    fin.read((char*)&user, sizeof(user));
    while (!fin.fail()){
        if(strcmp(id, user.uID) == 0 && strcmp(pwd, user.uPwd) == 0){   //验证通过
            fin.close();
            return true;
        }else if(strcmp(id, user.uID) == 0){                    //密码错误
            idFlag = true;
        }
        fin.read((char*)&user, sizeof(user));
    }
    if(idFlag){
        throw MyException("密码错误!");
    }else{
        throw MyException("无此用户!");
    }
    return false;
}

int main(int argc, char const *argv[]){
    User user;
    user.createUsers("nancy", "123456Nancy");           //ID头部不对
    user.createUsers("DavidDDDDDDD", "Password111");    //ID长度不对
    user.createUsers("Jack", "qwe123ASD1111111111111111");  //密码长度不对
    user.createUsers("Poul", "poul123");                //密码不包含大小写

    user.createUsers("Nancy", "123456Nancy");
    user.createUsers("David", "Password111");
    user.createUsers("Jack", "qwe123ASD");
    user.createUsers("Poul", "Poul123");

    User user2;
    user2.verifyUsers("Nancy", "123456Nancy");      //通过
    user2.verifyUsers("David", "Password");         //密码错误
    user2.verifyUsers("Poul2", "Poul123");          //无此用户
    user2.verifyUsers("Mike", "");                  //未输入密码
    user2.verifyUsers("", "123");                   //未输入用户名
    return 0;
}

