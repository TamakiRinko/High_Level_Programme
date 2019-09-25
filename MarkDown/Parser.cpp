//
// Created by TamakiRinko on 2019/9/23.
//

#include "Parser.h"

//regex SERegex("(\\*\\*\\*)(.+?)(\\*\\*\\*)");       //加粗斜体
//regex SRegex("(\\*\\*)(.+?)(\\*\\*)");              //加粗
//regex ERegex("(\\*)(.+?)(\\*)");                    //斜体
regex SERegex(R"((\*\*\*)(.+?)(\*\*\*))");       //加粗斜体
regex SRegex(R"((\*\*)(.+?)(\*\*))");              //加粗
regex ERegex(R"((\*)(.+?)(\*))");                    //斜体
regex H1Regex(R"(# )");                               //h1
regex H2Regex(R"(## )");                              //h2
regex H3Regex(R"(### )");                             //h3
regex H4Regex(R"(#### )");                            //h4
regex H5Regex(R"(##### )");                           //h5
regex H6Regex(R"(###### )");                          //h6
regex LIRegex(R"(^[*+-] )");                           //列表
//regex LIORegex("^(\\d+)\\.");                         //有序列表
regex LIORegex(R"(^(\d+)\.)");
//regex LKSRegex("\\[(.*)\\]\\((.+)\\)");             //链接
regex LKSRegex(R"(\[(.*)\]\((.+)\))");

Parser::Parser(const char *inFileName, const char* outFileName) {
    print(inFileName);
    print(outFileName);
    fin.open(inFileName, ios::in);
    fout.open(outFileName, ios::out);
    if(!fin.is_open()){
        print("Fin File open error!\n");
        return;
    }
    if(!fout.is_open()){
        print("Fout File open error!\n");
        return;
    }
    htmlStr = htmlStart;
    curStatus = NORMAL;
    listLevel = 0;
    blankNum = 0;
}

void Parser::Handle() {
    string curStr = "";
    while(getline(fin, curStr)){
        blankHandle(curStr);
        int curListLevel = listCount(curStr);
        if(regex_search(curStr, LIRegex)){                                      //当前一行为LISTS
            if(curStatus == NORMAL){                                            //新的LISTS
                curStatus = LISTS;
                listLevel = 1;
                curStr = regex_replace(curStr, LIRegex, "<ul>\n<li>");
                REHandle(curStr);
                myStack.push("</ul>\n");
                myStack.push("</li>\n");
            }else if(curStatus == LISTS || curStatus == ORDEREDLISTS){          //嵌套LISTS
                curStatus = LISTS;
                if(curListLevel > listLevel){                                   //子列表
                    listLevel = curListLevel;
                    curStr = regex_replace(curStr, LIRegex, "<ul>\n<li>");
                    REHandle(curStr);
                    myStack.push("</ul>\n");
                    myStack.push("</li>\n");
                } else if(curListLevel == listLevel){                           //同级列表，前一个一定为LISTS
                    string prefix = "";
                    while(myStack.top() != "</ul>\n"){
                        prefix += myStack.top();
                        myStack.pop();
                    }
                    curStr = regex_replace(curStr, LIRegex, "<li>");
                    myStack.push("</li>\n");
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }else{                                                          //父列表
                    int popNum = listLevel - curListLevel;
                    string prefix = "";
                    while(popNum >= 0){
                        if(myStack.top() == "</ul>\n" || myStack.top() == "</ol>\n"){   //之前可能为LISTS或ORDEREDLISTS
                            popNum--;
                        }
                        if(popNum != -1){                                       //保留同级的/ul
                            prefix += myStack.top();
                            myStack.pop();
                        }
                    }
                    curStr = regex_replace(curStr, LIRegex, "<li>");
                    myStack.push("</li>\n");
                    listLevel = curListLevel;
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }
            }
        }else if(regex_search(curStr, LIORegex)){                               //当前一行为ORDEREDLISTS
            if(curStatus == NORMAL){                                            //新的ORDEREDLISTS
                curStatus = ORDEREDLISTS;
                listLevel = 1;
                curStr = regex_replace(curStr, LIORegex, "<ol start=\'$1\'>\n<li>");
                REHandle(curStr);
                myStack.push("</ol>\n");
                myStack.push("</li>\n");
            }else if(curStatus == LISTS || curStatus == ORDEREDLISTS){          //嵌套ORDEREDLISTS
                curStatus = ORDEREDLISTS;
                if(curListLevel > listLevel){                                   //子列表
                    listLevel = curListLevel;
                    curStr = regex_replace(curStr, LIORegex, "<ol start=\'$1\'>\n<li>");
                    REHandle(curStr);
                    myStack.push("</ol>\n");
                    myStack.push("</li>\n");
                } else if(curListLevel == listLevel){                           //同级列表
                    string prefix = "";
                    while(myStack.top() != "</ol>\n"){
                        prefix += myStack.top();
                        myStack.pop();
                    }
                    curStr = regex_replace(curStr, LIORegex, "<li>");
                    myStack.push("</li>\n");
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }else{                                                          //父列表
                    int popNum = listLevel - curListLevel;
                    string prefix = "";
                    while(popNum >= 0){
                        if(myStack.top() == "</ol>\n" || myStack.top() == "</ul>\n"){   //前面可能是LISTS
                            popNum--;
                        }
                        if(popNum != -1){                                       //保留同级的/ol
                            prefix += myStack.top();
                            myStack.pop();
                        }
                    }
                    curStr = regex_replace(curStr, LIORegex, "<li>");
                    myStack.push("</li>\n");
                    listLevel = curListLevel;
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }
            }
        }else if(curStatus == LISTS || curStatus == ORDEREDLISTS){
            if(curStr != ""){                                   //来了新的一类，不再是列表
                while(!myStack.empty()){                        //栈中弹出剩余的结束标签
                    htmlStr += myStack.top();
                    myStack.pop();
                }
                REHandle(curStr);
                curStatus = NORMAL;
                listLevel = 0;
            }
//            if(curStr == "&nbsp;"){         //变为空行了
//                string prefix = "";
//                while(!myStack.empty()){
//                    prefix += myStack.top();
//                    myStack.pop();
//                }
//                curStr = prefix + curStr;
//                curStatus = NORMAL;
//                listLevel = 0;
//                REHandle(curStr);
//            }
        }
//        else if(curStatus == LISTS || curStatus == ORDEREDLISTS){
//            while(!myStack.empty()){
//                curStr += myStack.top();
//                myStack.pop();
//            }
//            REHandle(curStr);   //处理时仍是LISTS状态
//            curStatus = NORMAL;
//            listLevel = 0;
//        }
        else if(curStr != ""){                              //新的非空一行
            while(!myStack.empty()){                        //栈中弹出剩余的结束标签
                htmlStr += myStack.top();
                myStack.pop();
            }
            REHandle(curStr);
        }
        htmlStr += curStr;
    }
    while(!myStack.empty()){
        htmlStr += myStack.top();
        myStack.pop();
    }
    htmlStr += htmlEnd;
    fout << htmlStr;
    fout.close();
}

int Parser::listCount(string& str) {
    int num = 0;
    int i = 0;
    while(str[i] == ' '){
        num++;
        i++;
    }
    str = str.substr(i);
    return (num / 2) + 1;
}

void Parser::REHandle(string &curStr) {
    bool isHead = false;
    if(regex_search(curStr, H6Regex)){
        curStr = regex_replace(curStr, H6Regex, "<h6>");
        curStr = curStr + "</h6>\n";
        isHead = true;
    }else if(regex_search(curStr, H5Regex)){
        curStr = regex_replace(curStr, H5Regex, "<h5>");
        curStr = curStr + "</h5>\n";
        isHead = true;
    }else if(regex_search(curStr, H4Regex)){
        curStr = regex_replace(curStr, H4Regex, "<h4>");
        curStr = curStr + "</h4>\n";
        isHead = true;
    }else if(regex_search(curStr, H3Regex)){
        curStr = regex_replace(curStr, H3Regex, "<h3>");
        curStr = curStr + "</h3>\n";
        isHead = true;
    }else if(regex_search(curStr, H2Regex)){
        curStr = regex_replace(curStr, H2Regex, "<h2>");
        curStr = curStr + "</h2>\n";
        isHead = true;
    }else if(regex_search(curStr, H1Regex)){
        curStr = regex_replace(curStr, H1Regex, "<h1>");
        curStr = curStr + "</h1>\n";
        isHead = true;
    }
    curStr = regex_replace(curStr, SERegex, "<strong><em>$2</em></strong>");
    curStr = regex_replace(curStr, SRegex, "<strong>$2</strong>");
    curStr = regex_replace(curStr, ERegex, "<em>$2</em>");
    curStr = regex_replace(curStr, LKSRegex, "<a href=\'$2\'>$1</a>");
    if(!isHead && listLevel == 0 && curStr != ""){      //列表中不添加<p>
        curStr = "<p>" + curStr + "</p>\n";
    }
}

void Parser::blankHandle(string &curStr) {
    if(curStr == ""){
        blankNum++;
    }
    if(curStr != ""){
        blankNum = 0;
    }
    if(blankNum == 3){          //空三行，增加一个空行，变为一般类型
        curStr = "&nbsp;";
        blankNum = 0;
        curStatus = NORMAL;
        listLevel = 0;
    }
}