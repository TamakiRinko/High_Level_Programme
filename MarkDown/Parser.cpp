//
// Created by TamakiRinko on 2019/9/23.
//

#include "Parser.h"

//regex SERegex("(\\*\\*\\*)(.+?)(\\*\\*\\*)");       //�Ӵ�б��
//regex SRegex("(\\*\\*)(.+?)(\\*\\*)");              //�Ӵ�
//regex ERegex("(\\*)(.+?)(\\*)");                    //б��
regex SERegex(R"((\*\*\*)(.+?)(\*\*\*))");       //�Ӵ�б��
regex SRegex(R"((\*\*)(.+?)(\*\*))");              //�Ӵ�
regex ERegex(R"((\*)(.+?)(\*))");                    //б��
regex H1Regex(R"(# )");                               //h1
regex H2Regex(R"(## )");                              //h2
regex H3Regex(R"(### )");                             //h3
regex H4Regex(R"(#### )");                            //h4
regex H5Regex(R"(##### )");                           //h5
regex H6Regex(R"(###### )");                          //h6
regex LIRegex(R"(^[*+-] )");                           //�б�
//regex LIORegex("^(\\d+)\\.");                         //�����б�
regex LIORegex(R"(^(\d+)\.)");
//regex LKSRegex("\\[(.*)\\]\\((.+)\\)");             //����
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
        if(regex_search(curStr, LIRegex)){                                      //��ǰһ��ΪLISTS
            if(curStatus == NORMAL){                                            //�µ�LISTS
                curStatus = LISTS;
                listLevel = 1;
                curStr = regex_replace(curStr, LIRegex, "<ul>\n<li>");
                REHandle(curStr);
                myStack.push("</ul>\n");
                myStack.push("</li>\n");
            }else if(curStatus == LISTS || curStatus == ORDEREDLISTS){          //Ƕ��LISTS
                curStatus = LISTS;
                if(curListLevel > listLevel){                                   //���б�
                    listLevel = curListLevel;
                    curStr = regex_replace(curStr, LIRegex, "<ul>\n<li>");
                    REHandle(curStr);
                    myStack.push("</ul>\n");
                    myStack.push("</li>\n");
                } else if(curListLevel == listLevel){                           //ͬ���б�ǰһ��һ��ΪLISTS
                    string prefix = "";
                    while(myStack.top() != "</ul>\n"){
                        prefix += myStack.top();
                        myStack.pop();
                    }
                    curStr = regex_replace(curStr, LIRegex, "<li>");
                    myStack.push("</li>\n");
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }else{                                                          //���б�
                    int popNum = listLevel - curListLevel;
                    string prefix = "";
                    while(popNum >= 0){
                        if(myStack.top() == "</ul>\n" || myStack.top() == "</ol>\n"){   //֮ǰ����ΪLISTS��ORDEREDLISTS
                            popNum--;
                        }
                        if(popNum != -1){                                       //����ͬ����/ul
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
        }else if(regex_search(curStr, LIORegex)){                               //��ǰһ��ΪORDEREDLISTS
            if(curStatus == NORMAL){                                            //�µ�ORDEREDLISTS
                curStatus = ORDEREDLISTS;
                listLevel = 1;
                curStr = regex_replace(curStr, LIORegex, "<ol start=\'$1\'>\n<li>");
                REHandle(curStr);
                myStack.push("</ol>\n");
                myStack.push("</li>\n");
            }else if(curStatus == LISTS || curStatus == ORDEREDLISTS){          //Ƕ��ORDEREDLISTS
                curStatus = ORDEREDLISTS;
                if(curListLevel > listLevel){                                   //���б�
                    listLevel = curListLevel;
                    curStr = regex_replace(curStr, LIORegex, "<ol start=\'$1\'>\n<li>");
                    REHandle(curStr);
                    myStack.push("</ol>\n");
                    myStack.push("</li>\n");
                } else if(curListLevel == listLevel){                           //ͬ���б�
                    string prefix = "";
                    while(myStack.top() != "</ol>\n"){
                        prefix += myStack.top();
                        myStack.pop();
                    }
                    curStr = regex_replace(curStr, LIORegex, "<li>");
                    myStack.push("</li>\n");
                    curStr = prefix + curStr;
                    REHandle(curStr);
                }else{                                                          //���б�
                    int popNum = listLevel - curListLevel;
                    string prefix = "";
                    while(popNum >= 0){
                        if(myStack.top() == "</ol>\n" || myStack.top() == "</ul>\n"){   //ǰ�������LISTS
                            popNum--;
                        }
                        if(popNum != -1){                                       //����ͬ����/ol
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
            if(curStr != ""){                                   //�����µ�һ�࣬�������б�
                while(!myStack.empty()){                        //ջ�е���ʣ��Ľ�����ǩ
                    htmlStr += myStack.top();
                    myStack.pop();
                }
                REHandle(curStr);
                curStatus = NORMAL;
                listLevel = 0;
            }
//            if(curStr == "&nbsp;"){         //��Ϊ������
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
//            REHandle(curStr);   //����ʱ����LISTS״̬
//            curStatus = NORMAL;
//            listLevel = 0;
//        }
        else if(curStr != ""){                              //�µķǿ�һ��
            while(!myStack.empty()){                        //ջ�е���ʣ��Ľ�����ǩ
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
    if(!isHead && listLevel == 0 && curStr != ""){      //�б��в����<p>
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
    if(blankNum == 3){          //�����У�����һ�����У���Ϊһ������
        curStr = "&nbsp;";
        blankNum = 0;
        curStatus = NORMAL;
        listLevel = 0;
    }
}