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
//    string s = "# 一级标题\n"
//               "\n"
//               "## 二级标题\n"
//               "\n"
//               "###  三级标题\n"
//               "\n"
//               "\n"
//               "\n"
//               "普通文本， **加粗文本**， *斜体文本*， ***加粗斜体文本***\n"
//               "\n"
//               "链接：[百度](http://baidu.com)\n"
//               "\n"
//               "#### 无序列表\n"
//               "\n"
//               "+ 列表项一\n"
//               "+ 列表项二\n"
//               "+ 列表项三\n"
//               "\n"
//               "\n"
//               "\n"
//               "#### 有序列表\n"
//               "\n"
//               "1. 列表项一\n"
//               "2. 列表项二\n"
//               "3. 列表项三\n"
//               "\n"
//               "#### 嵌套列表\n"
//               "\n"
//               "+ 列表项1\n"
//               "  1. 子列表项1\n"
//               "  2. 子列表项2\n"
//               "+ 列表项2\n"
//               "  + 子列表项1\n"
//               "  + 子列表项2\n"
//               "\n"
//               "\n"
//               "\n"
//               "#### 多个语法混合\n"
//               "\n"
//               "+ #### *倾斜标题列表项* \n"
//               "\n"
//               "+ 链接列表项，[计算机系主页](http://cs.nju.edu.cn)\n"
//               "\n"
//               "+ ##### 标题链接列表项 [计算机系主页](http://cs.nju.edu.cn)\n"
//               "\n"
//               "+ 倾斜加粗链接 ***[计算机系主页](http://cs.nju.edu.cn)***\n"
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
////    regex pattern("\\d{4}");	//匹配四个数字
////
//////迭代器声明
////    string::const_iterator iterStart = str.begin();
////    cout << "first: " << *iterStart << endl;
////    string::const_iterator iterEnd = str.end();
////    string temp;
////    while (regex_search(iterStart, iterEnd, result, pattern))
////    {
////        temp = result[0];
////        cout << temp << " \n";
////        iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
////        cout << *iterStart << endl;
////    }
////
////}


int main(){
    Parser parser("../try.md", "../result.html");
    parser.Handle();
}