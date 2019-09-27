//
// Created by TamakiRinko on 2019/9/25.
//

#include "Parser.h"
string Values::htmlStart = "<!doctype html>\n"
                           "<html>\n"
                           "<head>\n"
                           "<meta charset='UTF-8'><meta name='viewport' content='width=device-width initial-scale=1'>\n"
                           "<title>样例</title></head>\n"
                           "<body>\n";
string Values::htmlEnd = "</body>\n"
                         "</html>";
regex Values::SERegex(R"((\*\*\*)(.+?)(\*\*\*))");              //加粗斜体
regex Values::SRegex(R"((\*\*)(.+?)(\*\*))");                   //加粗
regex Values::ERegex(R"((\*)(.+?)(\*))");                       //斜体
regex Values::H1Regex(R"(^# )");                                 //h1
regex Values::H2Regex(R"(^## )");                                //h2
regex Values::H3Regex(R"(^### )");                               //h3
regex Values::H4Regex(R"(^#### )");                              //h4
regex Values::H5Regex(R"(^##### )");                             //h5
regex Values::H6Regex(R"(^###### )");                            //h6
regex Values::LIRegex(R"(^[*+-] )");                            //列表
regex Values::LIORegex(R"(^(\d+)\.)");                          //有序列表
regex Values::LKSRegex(R"(\[(.*)\]\((.+)\))");                  //链接
regex Values::BLQRegex(R"(^> )");                               //BlockQuote
regex Values::IMGRegex(R"(!\[(.*)\]\((.+)\))");                 //图片