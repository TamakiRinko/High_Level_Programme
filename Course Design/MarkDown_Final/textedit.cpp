#include "textedit.h"

TextEdit::TextEdit(QWidget* parent): QTextEdit(parent){
    levelList.push_back(0);                             //初始默认为0层
//    setTabChangesFocus(false);
//    QFontMetrics metrics(font());
//    setTabStopWidth(8 * metrics.width(' '));            //8????
}

void TextEdit::keyPressEvent(QKeyEvent* e){
    if((e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Tab)){                 //Ctrl+Tab，回退
        int lineNum = textCursor().blockNumber();
        QString contents = document()->findBlockByNumber(lineNum).text();
        int level = lineLevel(contents);
        if(level == 0){
            e->ignore();
        }else{                                                                              //Level减少一级
            level -= 1;
            generateLevel(level, false);
        }
    }else if(e->key() == Qt::Key_Tab){                                                      //Tab，前进
        int lineNum = textCursor().blockNumber();
        QString contents = document()->findBlockByNumber(lineNum).text();
        int level = lineLevel(contents);
        if(level == 0){
            textCursor().insertText("    ");
        }else{
            if(lineNum == 0){
                textCursor().insertText("    ");
            }else{
                QString preContents = document()->findBlockByNumber(lineNum - 1).text();
                int preLevel = lineLevel(preContents);
                if(preLevel == 0){
                    textCursor().insertText("    ");
                }else if(level <= preLevel){                                                //Level增加一级
                    level += 1;
                    generateLevel(level, false);
                }else{
                    textCursor().insertText("    ");
                }
            }
        }
    }else if(e->key() == Qt::Key_Return){                                                   //Return
        int lineNum = textCursor().blockNumber();
        QString contents = document()->findBlockByNumber(lineNum).text();
        int level = lineLevel(contents);
        if(level > 0){
            int preLevel = 0;
            if(lineNum > 0){
                QString preContents = document()->findBlockByNumber(lineNum - 1).text();
                preLevel = lineLevel(preContents);
            }

            if(preLevel < level - 1){
                level = preLevel + 1;
                generateLevel(level, false);
            }
        }
        QTextEdit::keyPressEvent(e);
        generateLevel(level, true);
    }else{
        QTextEdit::keyPressEvent(e);
    }
}

int TextEdit::lineLevel(QString contents){
    int num = 0;
    int i = 0;
    while(contents[i] == ' '){
        num++;
        i++;
    }
    if(contents[i] == '*' && i < contents.size() - 1 && contents[i + 1] == ' '){            //无序列表
        return num / 4 + 1;
    }else if(contents.split('.')[0].toInt()){                                               //有序列表
        return num / 4 + 1;
    }else{
        return 0;
    }
}

/**
 * @brief TextEdit::generateLevel
 * @param level
 * @param flag                              是否需要加上* 标记，若为空行则需要
 */
void TextEdit::generateLevel(int level, bool flag){
    int lineNum = textCursor().blockNumber();
    QString contents = document()->findBlockByNumber(lineNum).text();
    if(level == 0 && contents.mid(0, 2) == "* "){
        contents = contents.mid(2);
    }else if(level > 0){
        while(contents.size() > 0) {
            if(contents[0] == ' '){
                contents = contents.mid(1);
            }else{
                break;
            }
        }
        for(int i = 0; i < level - 1; ++i){
            contents = "    " + contents;
        }
        if(flag){
            contents = contents + "* ";
        }
    }
    QTextCursor qTextCursor = textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);                                    //插入修改后的内容
    qTextCursor.insertText(contents);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);             //删除原来的内容
    qTextCursor.removeSelectedText();
}
