#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<iostream>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include "Parser.h"
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool firstTime;                 //是否为第一次保存
    bool isInlineCSS;               //是否为内联式
    bool isOutCSS;                  //是否为外部式
    QTextEdit* mainText;            //编辑的文字
    QString fileName;               //当前文件名

    QMenuBar* menubar;              //菜单栏
    QMenu* fileMenu;                //文件菜单
    QMenu* operationMenu;           //操作栏
    QAction* newFileAction;         //新建文件
    QAction* openFileAction;        //打开文件
    QAction* saveFileAction;        //保存文件
    QAction* copyAction;            //复制
    QAction* pasteAction;           //粘贴
    QAction* cutAction;             //剪切
    QAction* strongAction;          //加粗
    QAction* italicAction;          //斜体
    QAction* h1Action;              //H1
    QAction* h2Action;              //H2
    QAction* h3Action;              //H3
    QAction* h4Action;              //H4
    QAction* h5Action;              //H5
    QAction* h6Action;              //H6
    QAction* imageAction;           //图片
    QAction* linkAction;            //链接
    QAction* codeAction;            //语句间代码
    QAction* mistakenAction;        //删除线
    QAction* horizonAction;         //水平线
    QAction* blockquoteAction;      //引用
    void setAction();               //设定槽函数
    void loadFile();                //加载一个文件
//    void selectBlock(QTextCharFormat fmt);      //设置光标的选区
protected slots:                    //槽函数
    void newFile();                 //新建文件
    void openFile();                //打开文件
    bool saveFile();                //保存文件
    void strong();                  //加粗
    void italic();                  //斜体
    void h1();                      //H1
    void h2();                      //H2
    void h3();                      //H3
    void h4();                      //H4
    void h5();                      //H5
    void h6();                      //H6
    void image();                   //图片
    void link();                    //链接
    void code();                    //语句间代码
    void mistaken();                //删除线
    void horizon();                 //水平线
    void blockquote();              //引用
    void closeEvent(QCloseEvent* event);         //关闭时的操作

};

#endif // MAINWINDOW_H
