#include "Parser.h"

int main(){
    print("����1, �������ʽCSS��ʽ\t����2, ����ⲿʽCSS��ʽ\t����, �����CSS��ʽ");
    string x = "";
    cin >> x;
    if(x == "1"){
        Values::isInlineCSS = true;
    }else if(x == "2"){
        Values::isOutCSS = true;
    }
    Parser parser("../SRCFile/try.md", "../RESFile/result3.html");
    parser.Handle();
}