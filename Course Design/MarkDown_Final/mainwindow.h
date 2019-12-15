#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QDebug>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
//#include <QTextEdit>
#include <QTextStream>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QWebEngineView>
#include <QTimer>
#include <cstdio>
#include <QPalette>
#include <QProcess>
#include <QTextCursor>
#include "parser.h"
#include "htmlwindow.h"
#include "painterwindow.h"
#include "screenshot.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void screenShot();                                          //截屏快捷键
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    HTMLWindow* htmlWindow;         //html显示窗口
    QString htmlFileName;           //html文件的名称
    QString tempHtmlFileName;       //html临时文件的名称
    bool firstTime;                 //是否为第一次保存
    bool isInlineCSS;               //是否为内联式
    bool isOutCSS;                  //是否为外部式

    QString fileName;               //导入文件名
    QString thisFileName;           //当前打开文件名
    QString tempThisFileName;       //当前打开文件的临时文件名
    QString pdfThisFileName;        //导出的PDF名称

    QTimer* htmlSyncTimer;          //同步显示时钟
    bool needToSync;                //需要同步
    QTimer* modifiedTimer;          //检测修改的时钟
    bool isModified;                //内容有修改

    PainterWindow* painterWindow;   //绘图窗口
    QString painterName;            //绘图图片名称
    QString backgroundFileName;     //绘图背景图片名称

    ScreenShot* curScreenShot;      //截屏
    QString screenShotName;         //截屏图片名称

    void loadFile(QString fileName);//加载一个文件
    bool saveFile();                //保存文件
    void handleFile();              //转换成HTML文件并展示
    void parser(QString inFileName, QString outFileName);           //处理
    void closeEvent(QCloseEvent* event);         //关闭时的操作


    void selectPart(QTextCursor* qTextCursor,  int start, int end);
    void deleteContents(QTextCursor* qTextCursor, int pos, int num);
    int strongOritalic(QString selectedContents);

private slots:
    void onHtmlSyncTimerOut();
    void onModifiedTimerOut();
    void on_newFileAction_triggered();
    void on_openFileAction_triggered();
    void on_saveFileAction_triggered();
    void on_saveFileButton_clicked();
    void on_strongAction_triggered();
    void on_italicAction_triggered();
    void on_h1Action_triggered();
    void on_h2Action_triggered();
    void on_h3Action_triggered();
    void on_h4Action_triggered();
    void on_h5Action_triggered();
    void on_h6Action_triggered();
    void on_imageAction_triggered();
    void on_linkAction_triggered();
    void on_codeAction_triggered();
    void on_mistakenAction_triggered();
    void on_horizonAction_triggered();
    void on_blockquoteAction_triggered();
    void on_strongButton_clicked();
    void on_ItalicButton_clicked();
    void on_imageButton_clicked();
    void on_linkButton_clicked();
    void on_codeButton_clicked();
    void on_mistakenButton_clicked();
    void on_horizonButton_clicked();
    void on_blockQuoteButton_clicked();
    void on_convertToPDFAction_triggered();
    void on_painterAction_triggered();
    void on_painterButton_clicked();
    void on_screenshotAction_triggered();
    void on_screenshotButton_clicked();

    void painterCloseEvent();       //绘图器关闭后的操作
};

#endif // MAINWINDOW_H
