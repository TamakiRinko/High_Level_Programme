#include "Parser.h"

int main(){
    print("输入1, 输出内联式CSS样式\t输入2, 输出外部式CSS样式\t否则, 输出无CSS样式");
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