#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBlock>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QFont>

class TextEdit: public QTextEdit{
    Q_OBJECT
public:
    explicit TextEdit(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* e);
    int getLineLevel(int i);
private:
//    QList<int> levelList;

    int lineLevel(QString contents);                                    //仅考虑*
    int lineLevelAll(QString contents);                                 //考虑所有可能的列表类型
    void generateLevel(int level, bool flag);                           //根据level修改当前行
};

#endif // TEXTEDIT_H
