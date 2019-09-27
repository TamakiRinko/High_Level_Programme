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
        if(regex_search(curStr, Values::LIRegex)){                                      //��ǰһ��ΪLISTS
            listLogic(curStr, curListLevel, Values::LISTS, Values::LIRegex,
                    "<ul>\n<li>", "</ol>\n",
                    "</ul>\n", "<li>", "</li>\n");
        }else if(regex_search(curStr, Values::LIORegex)){                               //��ǰһ��ΪORDEREDLISTS
            listLogic(curStr, curListLevel, Values::ORDEREDLISTS, Values::LIORegex,
                    "<ol start=\'$1\'>\n<li>", "</ul>\n",
                    "</ol>\n", "<li>", "</li>\n");
        }else if(curStatus == Values::LISTS || curStatus == Values::ORDEREDLISTS){              //ֻ���������л���һ���ǿ��вŻ�����б�
            if(curStr != ""){                                                   //�����µ�һ�࣬�������б�
                while(!myStack.empty()){                                        //ջ�е���ʣ��Ľ�����ǩ
                    htmlStr += myStack.top();
                    myStack.pop();
                }
                curStatus = Values::NORMAL;                                     //��ʱ�Ѿ��������б���
                listLevel = 0;
                REHandle(curStr);
            }
        }else if(curStr != ""){                                                 //�µķǿ�һ��
            REHandle(curStr);
        }
        htmlStr += curStr;
    }
    while(!myStack.empty()){                                                    //�б�����ĩβʱ����������
        htmlStr += myStack.top();
        myStack.pop();
    }
    if(blqFlag){                                                                //blockquote����ĩβ
        htmlStr += "</p></blockquote>\n";
    }
    htmlStr += Values::htmlEnd;
    fout << htmlStr;
    fout.close();
}

/**
 * ���㵱ǰ�о��׿ո���
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
 * ������ʽ������
 * @param curStr
 */
void Parser::REHandle(string &curStr, regex* myRegex, string label) {
    if(curStr == "")    return;
    string temp1;
    string temp2;
    if(curStr.length() >= 2){
        temp1 = curStr.substr(2);                //�󲿷�
        temp2 = curStr.substr(0, 2);         //ǰ����
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
    }else if(curStr.length() == 1 && curStr[0] == '>' && blqFlag){  //>:�����У������Ƕ��>�����
        curStr = "</p>\n";
        blqMatch = true;
    }else if(blqFlag){                                              //blockquote���������һ����ͨ��
        htmlStr += "</p></blockquote>\n";
        blqFlag = false;
    }
    if(!isHead && listLevel == 0 && curStr != "" && !blqFlag){      //�б��в����<p>
        curStr = "<p>" + curStr + "</p>\n";
    }else if(listLevel != 0){
        curStr = temp2 + curStr;
    }
//    print("last " + curStr);
//    cout << endl;
}

/**
 * �հ��д���3��������һ��&nbsp;
 * @param curStr
 */
void Parser::blankHandle(string &curStr) {
    if(curStr == ""){
        if(blqFlag){                                //blockquote���������Ϊ����
            blqFlag = false;
            htmlStr += "</p></blockquote>\n";
        }
        blankNum++;
    }
    if(curStr != ""){
        blankNum = 0;
    }
    if(blankNum == 3){          //�����У�����һ�����У���Ϊһ������
        curStr = "&nbsp;";
        blankNum = 0;
    }
}

/**
 * ����LISTS��ORDEREDLISTS���߼�
 * @param curStr                //��ǰ���ַ���
 * @param curListLevel          //��ǰ�б����
 * @param status                //��ǰStatus
 * @param myRegex               //ʹ�õ�������ʽ
 * @param startLabel            //�µ�һ���б�ʼ�ַ���
 * @param otherLabel            //�Է��Ľ����ַ���(LISTSʱΪ</ol>)
 * @param endLabel              //�����Ľ����ַ���(LISTSʱΪ</ul>)
 * @param comStartLabel         //<li>
 * @param comEndLabel           //</li>
 */
void Parser::listLogic(string &curStr, int curListLevel, Values::Status status, regex myRegex,
        string startLabel, string otherLabel, string endLabel, string comStartLabel, string comEndLabel) {
    if(curStatus == Values::NORMAL){                                            //�µ�LISTS
        curStatus = status;
        listLevel = 1;
        myStack.push(endLabel);                                      //��������ѹ��ջ��
        myStack.push(comEndLabel);
        REHandle(curStr, &myRegex, startLabel);                                            //���ಿ�ִ���
    }else if(curStatus == Values::LISTS || curStatus == Values::ORDEREDLISTS){          //Ƕ��LISTS
        curStatus = status;
        if(curListLevel > listLevel){                                   //��ǰΪ���б�Ӧ��ʼ�µ�һ���б�
            myStack.push(endLabel);
            myStack.push(comEndLabel);
            listLevel = curListLevel;
            REHandle(curStr, &myRegex, startLabel);
        } else if(curListLevel == listLevel){                           //ͬ���б����ͱ�Ȼ��ͬ
            while(myStack.top() != endLabel){                           //ֱ��ֻʣ�б������</ul>��</ol>
                htmlStr += myStack.top();
                myStack.pop();
            }
            myStack.push(comEndLabel);
            REHandle(curStr, &myRegex, comStartLabel);
        }else{                                                          //���б�
            int popNum = listLevel - curListLevel;                      //�����Ĳ���
            while(popNum >= 0){
                if(myStack.top() == endLabel || myStack.top() == otherLabel){   //֮ǰ����ΪLISTS��ORDEREDLISTS
                    popNum--;
                }
                if(popNum != -1){                                       //����ͬ����/ul
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
