//
// Created by TamakiRinko on 2019/9/23.
//

#ifndef MARKDOWN_PARSER_H
#define MARKDOWN_PARSER_H

#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

#define print(x) cout << x << endl

/**
 * 当前所在状态
 * @NORMAL          正常
 * @LISTS           无序列表
 * @ORDEREDLISTS    有序列表
 */


class Values{
public:
    static bool isInlineCSS;
    static bool isOutCSS;
    enum Status{
        NORMAL, LISTS, ORDEREDLISTS
    };
    //开头部分
    static string htmlStart;
    //结尾部分
    static string htmlEnd;
    //外部式CSS开头
    static string CSSStart;
    //正则表达式
    static regex SERegex;
    static regex SRegex;
    static regex ERegex;
    static regex H1Regex;
    static regex H2Regex;
    static regex H3Regex;
    static regex H4Regex;
    static regex H5Regex;
    static regex H6Regex;
    static regex LIRegex;
    static regex LIORegex;
    static regex LKSRegex;
    static regex BLQRegex;
    static regex IMGRegex;
    static regex HORLINRegex;
    static regex CODERegex;
    static regex MTNRegex;
};



class Parser{
public:
    Parser(const char* inFileName, const char* outFileName);
    void Handle();
private:
    ifstream fin;               //读入文件描述符
    ofstream fout;              //读出文件描述符
    string htmlStr;             //最终html字符串
    Values::Status curStatus;   //当前status
    stack<string> myStack;      //存储结束符的栈
    int listLevel;              //当前列表层数
    int blankNum;               //空行数目，达到3则增加&nbsp;
    bool blqFlag;               //判断之前是否为blockquote
    bool blqMatch;              //blq的<p>与</p>是否配对
    void handleLine(string& curStr);    //处理每一行的整体逻辑
    int listCount(string& str); //计算当前行的层数
    void REHandle(string &curStr, regex *myRegex = nullptr, string label = "");     //正则表达式处理
    void handleHtml(string &curStr, regex *myRegex, string label);      //输出HTML样式
    void handleCSS(string &curStr, regex *myRegex, string label);       //输出CSS样式
    void blankHandle(string& curStr);                                                   //空格处理
    void listLogic(string &curStr, int curListLevel, Values::Status status, regex myRegex,
                   string startLabel, string otherLabel, string endLabel, string comStartLabel, string comEndLabel);
    void blqLogic(string& curStr);
};

#endif