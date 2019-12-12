#include "mainwindow.h"
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
//    MainWindow w(true);
    MainWindow w;
    w.show();
    return a.exec();

}
