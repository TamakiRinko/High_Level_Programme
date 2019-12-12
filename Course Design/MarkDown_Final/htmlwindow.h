#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

namespace Ui {
class HTMLWindow;
}

class HTMLWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HTMLWindow(QWidget *parent = nullptr);
    void loadFile(QString fileName);                //加载一个文件
    ~HTMLWindow();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::HTMLWindow *ui;
    QWebEngineView* webView;
};

#endif // HTMLWINDOW_H
