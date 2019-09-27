//
// Created by TamakiRinko on 2019/9/23.
//
#include "Parser.h"

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
    htmlStr = Values::htmlStart;
    curStatus = Values::NORMAL;
    listLevel = 0;
    blankNum = 0;
    blqFlag = false;
    blqMatch = false;
}

void Parser::Handle() {
    string curStr = "";
    while(getline(fin, curStr)){
        blankHandle(curStr);
        int curListLevel = listCount(curStr);
        if(regex_search(curStr, Values::LIRegex)){                                      //当前一行为LISTS
            listLogic(curStr, curListLevel, Values::LISTS, Values::LIRegex,
                    "<ul>\n<li>", "</ol>\n",
                    "</ul>\n", "<li>", "</li>\n");
        }else if(regex_search(curStr, Values::LIORegex)){                               //当前一行为ORDEREDLISTS
            listLogic(curStr, curListLevel, Values::ORDEREDLISTS, Values::LIORegex,
                    "<ol start=\'$1\'>\n<li>", "</ul>\n",
                    "</ol>\n", "<li>", "</li>\n");
        }else if(curStatus == Values::LISTS || curStatus == Values::ORDEREDLISTS){              //只有三个空行或是一个非空行才会结束列表
            if(curStr != ""){                                                   //来了新的一类，不再是列表
                while(!myStack.empty()){                                        //栈中弹出剩余的结束标签
                    htmlStr += myStack.top();
                    myStack.pop();
                }
                curStatus = Values::NORMAL;                                     //此时已经不再是列表了
                listLevel = 0;
                REHandle(curStr);
            }
        }else if(curStr != ""){                                                 //新的非空一行
            REHandle(curStr);
        }
        htmlStr += curStr;
    }
    while(!myStack.empty()){                                                    //列表处于最末尾时弹出结束符
        htmlStr += myStack.top();
        myStack.pop();
    }
    if(blqFlag){                                                                //blockquote处于末尾
        htmlStr += "</p></blockquote>\n";
    }
    htmlStr += Values::htmlEnd;
    fout << htmlStr;
    fout.close();
}

/**
 * 计算当前行聚首空格数
 * @param str
 * @return
 */
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

/**
 * 正则表达式处理函数
 * @param curStr
 */
void Parser::REHandle(string &curStr, regex* myRegex, string label) {
    if(curStr == "")    return;
    string temp1;
    string temp2;
    if(curStr.length() >= 2){
        temp1 = curStr.substr(2);                //后部分
        temp2 = curStr.substr(0, 2);         //前部分
    }
//    print("this " + curStr);
    if(myRegex != nullptr){
        temp2 = regex_replace(temp2, *myRegex, label);
        curStr = temp1;
//        print(curStr);
    }
    bool isHead = false;
    if(regex_search(curStr, Values::H6Regex)){
        curStr = regex_replace(curStr, Values::H6Regex, "<h6>");
        curStr = curStr + "</h6>\n";
        isHead = true;
    }else if(regex_search(curStr, Values::H5Regex)){
        curStr = regex_replace(curStr, Values::H5Regex, "<h5>");
        curStr = curStr + "</h5>\n";
        isHead = true;
    }else if(regex_search(curStr, Values::H4Regex)){
        curStr = regex_replace(curStr, Values::H4Regex, "<h4>");
        curStr = curStr + "</h4>\n";
        isHead = true;
    }else if(regex_search(curStr, Values::H3Regex)){
        curStr = regex_replace(curStr, Values::H3Regex, "<h3>");
        curStr = curStr + "</h3>\n";
        isHead = true;
    }else if(regex_search(curStr, Values::H2Regex)){
        curStr = regex_replace(curStr, Values::H2Regex, "<h2>");
        curStr = curStr + "</h2>\n";
        isHead = true;
    }else if(regex_search(curStr, Values::H1Regex)){
        curStr = regex_replace(curStr, Values::H1Regex, "<h1>");
        curStr = curStr + "</h1>\n";
        isHead = true;
    }

    curStr = regex_replace(curStr, Values::SERegex, "<strong><em>$2</em></strong>");
    curStr = regex_replace(curStr, Values::SRegex, "<strong>$2</strong>");
    curStr = regex_replace(curStr, Values::ERegex, "<em>$2</em>");
    curStr = regex_replace(curStr, Values::IMGRegex, "<img src=\"$2\" alt=\"$1\">");
    curStr = regex_replace(curStr, Values::LKSRegex, "<a href=\'$2\'>$1</a>");

    if(regex_search(curStr, Values::BLQRegex)){                     //blockquote
        blqLogic(curStr);
    }else if(curStr.length() == 1 && curStr[0] == '>' && blqFlag){  //>:代表换行，不考虑多个>的情况
        curStr = "</p>\n";
        blqMatch = true;
    }else if(blqFlag){                                              //blockquote后面紧接着一个普通行
        htmlStr += "</p></blockquote>\n";
        blqFlag = false;
    }
    if(!isHead && listLevel == 0 && curStr != "" && !blqFlag){      //列表中不添加<p>
        curStr = "<p>" + curStr + "</p>\n";
    }else if(listLevel != 0){
        curStr = temp2 + curStr;
    }
//    print("last " + curStr);
//    cout << endl;
}

/**
 * 空白行处理，3个空行算一个&nbsp;
 * @param curStr
 */
void Parser::blankHandle(string &curStr) {
    if(curStr == ""){
        if(blqFlag){                                //blockquote后面紧接着为空行
            blqFlag = false;
            htmlStr += "</p></blockquote>\n";
        }
        blankNum++;
    }
    if(curStr != ""){
        blankNum = 0;
    }
    if(blankNum == 3){          //空三行，增加一个空行，变为一般类型
        curStr = "&nbsp;";
        blankNum = 0;
    }
}

/**
 * 处理LISTS和ORDEREDLISTS的逻辑
 * @param curStr                //当前行字符串
 * @param curListLevel          //当前列表层数
 * @param status                //当前Status
 * @param myRegex               //使用的正则表达式
 * @param startLabel            //新的一级列表开始字符串
 * @param otherLabel            //对方的结束字符串(LISTS时为</ol>)
 * @param endLabel              //本方的结束字符串(LISTS时为</ul>)
 * @param comStartLabel         //<li>
 * @param comEndLabel           //</li>
 */
void Parser::listLogic(string &curStr, int curListLevel, Values::Status status, regex myRegex,
        string startLabel, string otherLabel, string endLabel, string comStartLabel, string comEndLabel) {
    if(curStatus == Values::NORMAL){                                            //新的LISTS
        curStatus = status;
        listLevel = 1;
        myStack.push(endLabel);                                      //将结束符压入栈中
        myStack.push(comEndLabel);
        REHandle(curStr, &myRegex, startLabel);                                            //其余部分处理
    }else if(curStatus == Values::LISTS || curStatus == Values::ORDEREDLISTS){          //嵌套LISTS
        curStatus = status;
        if(curListLevel > listLevel){                                   //当前为子列表，应开始新的一级列表
            myStack.push(endLabel);
            myStack.push(comEndLabel);
            listLevel = curListLevel;
            REHandle(curStr, &myRegex, startLabel);
        } else if(curListLevel == listLevel){                           //同级列表，类型必然相同
            while(myStack.top() != endLabel){                           //直至只剩列表结束符</ul>或</ol>
                htmlStr += myStack.top();
                myStack.pop();
            }
            myStack.push(comEndLabel);
            REHandle(curStr, &myRegex, comStartLabel);
        }else{                                                          //父列表
            int popNum = listLevel - curListLevel;                      //弹出的层数
            while(popNum >= 0){
                if(myStack.top() == endLabel || myStack.top() == otherLabel){   //之前可能为LISTS或ORDEREDLISTS
                    popNum--;
                }
                if(popNum != -1){                                       //保留同级的/ul
                    htmlStr += myStack.top();
                    myStack.pop();
                }
            }
            myStack.push(comEndLabel);
            listLevel = curListLevel;
            REHandle(curStr, &myRegex, comStartLabel);
        }
    }
}

void Parser::blqLogic(string &curStr) {
    if(!blqFlag){
        curStr = regex_replace(curStr, Values::BLQRegex, "<blockquote>\n<p>");
        blqFlag = true;
        blqMatch = false;
    }else{
        if(blqMatch){
            curStr.replace(0, 2, "<p>");
            blqMatch = false;
        }else{
            curStr.replace(0, 2, "");
            curStr = " " + curStr;
        }
    }
}
