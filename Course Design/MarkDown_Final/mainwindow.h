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
#include <QWebEngineView>
#include <QTimer>
#include <cstdio>
#include "Parser.h"
#include "htmlwindow.h"
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
//    MainWindow* htmlWindow;         //展示html文件的窗口
    HTMLWindow* htmlWindow;
    QString htmlFileName;           //html文件的名称
    bool firstTime;                 //是否为第一次保存
    bool isInlineCSS;               //是否为内联式
    bool isOutCSS;                  //是否为外部式

    QTextEdit* mainText;            //编辑的文字
    QString fileName;               //导入文件名
    QString thisFileName;           //当前打开文件名
    QString tempThisFileName;       //当前打开文件的临时文件名
//    bool isMDFile;                  //当前打开文件是否为md文件

    QTimer* htmlSyncTimer;          //同步显示时钟
    bool needToSync;                //需要同步

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
    void loadFile(QString fileName);                //加载一个文件
    void setReadOnly();             //设定text为只读
    void setWritten();              //恢复可编辑

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
    void handleFile();              //转换成HTML文件并展示

    void onHtmlSyncTimerOut();

};

#endif // MAINWINDOW_H