#include <iostream>
#include <iterator>
#include <string>
#include <string.h>
#include "Parser.h"
using namespace std;

//
//
//void search();
//
//int main(){
//    regex SERegex("(\\*\\*\\*)(.+?)(\\*\\*\\*)");
//    regex SRegex("(\\*\\*)(.+?)(\\*\\*)");
//    regex ERegex("(\\*)(.+?)(\\*)");
//    regex H1Regex("^# ");
//    regex H2Regex("^## ");
//    regex H3Regex("^### ");
//    regex H4Regex("^#### ");
//    regex LIRegex("^[*+-] ");
//    smatch results;
//    string s = "# һ������\n"
//               "\n"
//               "## ��������\n"
//               "\n"
//               "###  ��������\n"
//               "\n"
//               "\n"
//               "\n"
//               "��ͨ�ı��� **�Ӵ��ı�**�� *б���ı�*�� ***�Ӵ�б���ı�***\n"
//               "\n"
//               "���ӣ�[�ٶ�](http://baidu.com)\n"
//               "\n"
//               "#### �����б�\n"
//               "\n"
//               "+ �б���һ\n"
//               "+ �б����\n"
//               "+ �б�����\n"
//               "\n"
//               "\n"
//               "\n"
//               "#### �����б�\n"
//               "\n"
//               "1. �б���һ\n"
//               "2. �б����\n"
//               "3. �б�����\n"
//               "\n"
//               "#### Ƕ���б�\n"
//               "\n"
//               "+ �б���1\n"
//               "  1. ���б���1\n"
//               "  2. ���б���2\n"
//               "+ �б���2\n"
//               "  + ���б���1\n"
//               "  + ���б���2\n"
//               "\n"
//               "\n"
//               "\n"
//               "#### ����﷨���\n"
//               "\n"
//               "+ #### *��б�����б���* \n"
//               "\n"
//               "+ �����б��[�����ϵ��ҳ](http://cs.nju.edu.cn)\n"
//               "\n"
//               "+ ##### ���������б��� [�����ϵ��ҳ](http://cs.nju.edu.cn)\n"
//               "\n"
//               "+ ��б�Ӵ����� ***[�����ϵ��ҳ](http://cs.nju.edu.cn)***\n"
//               "";
//    string::const_iterator iterStart = s.begin();
//    string::const_iterator iterEnd = s.end();
//    stringstream ss(s);
//    string sub_s;
//    string s_out = "";
//    while (getline(ss, sub_s, '\n')){
//        sub_s = regex_replace(sub_s, H4Regex, "<h4>");
//        sub_s = regex_replace(sub_s, H3Regex, "<h3>");
//        sub_s = regex_replace(sub_s, H2Regex, "<h2>");
//        sub_s = regex_replace(sub_s, H1Regex, "<h1>");
//        s_out = s_out + sub_s + "\n";
//    }
//    s = s_out;
//    string temp;
//    s = regex_replace(s, SERegex, "<strong><em>$2</em></strong>");
//    s = regex_replace(s, SRegex, "<strong>$2</strong>");
//    s = regex_replace(s, ERegex, "<em>$2</em>");
//    print(s);
////    while (regex_search(iterStart, iterEnd, results, SERegex)){
////        temp = results[0];
////        print(temp);
////        iterStart = results[0].second;
////    }
//    return 0;
//}
//
//
////void search(){
////    string str = "Hello 201834124, Bye 2017";
////    smatch result;
////    regex pattern("\\d{4}");	//ƥ���ĸ�����
////
//////����������
////    string::const_iterator iterStart = str.begin();
////    cout << "first: " << *iterStart << endl;
////    string::const_iterator iterEnd = str.end();
////    string temp;
////    while (regex_search(iterStart, iterEnd, result, pattern))
////    {
////        temp = result[0];
////        cout << temp << " \n";
////        iterStart = result[0].second;	//����������ʼλ��,����ʣ�µ��ַ���
////        cout << *iterStart << endl;
////    }
////
////}


int main(){
    Parser parser("../try.md", "../result.html");
    parser.Handle();
}