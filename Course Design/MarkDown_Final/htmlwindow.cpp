#include "htmlwindow.h"
#include "ui_htmlwindow.h"

HTMLWindow::HTMLWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::HTMLWindow){
    ui->setupUi(this);

    webView = new QWebEngineView(this);
}

HTMLWindow::~HTMLWindow(){
    delete ui;
}

void HTMLWindow::resizeEvent(QResizeEvent *){
    webView->resize(this->size());
}

void HTMLWindow::loadFile(QString fileName){
    webView->load(QUrl("file://" + fileName));
    webView->show();
}
