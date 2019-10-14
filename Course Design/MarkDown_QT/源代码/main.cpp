#include "mainwindow.h"
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <QApplication>

int main(int argc, char *argv[])
{
//    QDir temDir("markdownCSS.css");
//    QString filePath = temDir.absolutePath();
//    cout << filePath.toStdString();
//    struct passwd *user;
//    user = getpwuid(getuid());
//    QString currentPath;
//    QDir dir;
//    currentPath=dir.currentPath();
//    cout<<"path"<<currentPath.toStdString();
    QApplication a(argc, argv);
    MainWindow w(true);
    w.show();
//    cout << QCoreApplication::applicationFilePath().toStdString() << endl;
    return a.exec();

}
