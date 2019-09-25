//
// Created by TamakiRinko on 2019/9/23.
//

#ifndef MARKDOWN_PARSER_H
#define MARKDOWN_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <stack>
using namespace std;
#define print(x) cout << x << endl;
#define input(x) cin >> x

//开头部分
const string htmlStart = "<!doctype html>\n"
                     "<html>\n"
                     "<head>\n"
                     "    <meta charset='UTF-8'><meta name='viewport' content='width=device-width initial-scale=1'>\n"
                     "    <title>样例</title></head>\n"
                     "<body>\n";
//结尾部分
const string htmlEnd = "</body>\n"
                   "</html>";
//标签前部
const string beforeHtmlLabel[]{
    "<p>",
    "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>",
    "<strong>", "<em>", "<strong><em>",
    "<ul>", "<li>", "<ol>", "<ol start="
};
//标签后部
const string afterHtmlLabel[]{
    "</p>", "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>",
    "</strong>", "</em>", "</em></strong>", "</ul>", "</li>", "</ol>"
};
//与html不同的内容
const string diffContents[]{
    "&nbsp;"
};

/**
 * 当前所在状态
 */
enum Status{
    NORMAL, LISTS, ORDEREDLISTS, HEADERS, STRONG, EMPHASIS, LINKS
};

class Parser{
public:
    Parser(const char* inFileName, const char* outFileName);
    void Handle();
private:
    ifstream fin;
    ofstream fout;
    string htmlStr;
    Status curStatus;   //当前status
    stack<string> myStack;
    int listLevel;      //当前列表层数
    int listCount(string& str);
    void REHandle(string& curStr);
    void blankHandle(string& curStr);
    int blankNum;       //空行数目，大于2则增加&nbsp;
};


#endif //MARKDOWN_PARSER_H
