#include "mainwindow.h"
#include <QApplication>
#include <QHotkey>
#include <QKeySequence>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QHotkey* hotkey = new QHotkey(QKeySequence("Ctrl+Shift+A"), true);          //截图全局快捷键
    QObject::connect(hotkey,&QHotkey::activated,qApp,[&](){
        w.screenShot();
    });
    w.show();

    return a.exec();
}
