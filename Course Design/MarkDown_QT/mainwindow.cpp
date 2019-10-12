#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    fileName = "";
    firstTime = true;
    isOutCSS = false;
    isInlineCSS = false;
    this->resize(1000, 600);
    QFont font;
    font.setPointSize(16);
    mainText = new QTextEdit;
    mainText->setFont(font);
    setCentralWidget(mainText);
    setAction();

}

MainWindow::~MainWindow(){

}

void MainWindow::setAction(){
    menubar = menuBar();//菜单栏
    setMenuBar(menubar);//将菜单栏设置到窗口中
    fileMenu = menubar->addMenu("文件");
    operationMenu = menubar->addMenu("格式");

    //新建文件
    newFileAction = new QAction("新建");
    newFileAction->setShortcut(QKeySequence::New);
    connect(newFileAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    //打开文件
    openFileAction = new QAction("打开");
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    //保存文件
    saveFileAction = new QAction("保存");
    saveFileAction->setShortcut(QKeySequence::Save);
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    //复制
    copyAction = new QAction("复制");
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered(bool)), mainText, SLOT(copy()));

    //粘贴
    pasteAction = new QAction("粘贴");
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered(bool)), mainText, SLOT(paste()));

    //剪切
    cutAction = new QAction("剪切");
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, SIGNAL(triggered(bool)), mainText, SLOT(cut()));

    //H1
    h1Action = new QAction("一级标题");
    h1Action->setShortcut(tr("Ctrl+1"));
    connect(h1Action, SIGNAL(triggered(bool)), this, SLOT(h1()));

    //H2
    h2Action = new QAction("二级标题");
    h2Action->setShortcut(tr("Ctrl+2"));
    connect(h2Action, SIGNAL(triggered(bool)), this, SLOT(h2()));

    //H3
    h3Action = new QAction("三级标题");
    h3Action->setShortcut(tr("Ctrl+3"));
    connect(h3Action, SIGNAL(triggered(bool)), this, SLOT(h3()));

    //H4
    h4Action = new QAction("四级标题");
    h4Action->setShortcut(tr("Ctrl+4"));
    connect(h4Action, SIGNAL(triggered(bool)), this, SLOT(h4()));

    //H5
    h5Action = new QAction("五级标题");
    h5Action->setShortcut(tr("Ctrl+5"));
    connect(h5Action, SIGNAL(triggered(bool)), this, SLOT(h5()));

    //H6
    h6Action = new QAction("六级标题");
    h6Action->setShortcut(tr("Ctrl+6"));
    connect(h6Action, SIGNAL(triggered(bool)), this, SLOT(h6()));

    //加粗
    strongAction = new QAction("加粗");
    strongAction->setShortcut(tr("Ctrl+B"));
    connect(strongAction, SIGNAL(triggered(bool)), this, SLOT(strong()));

    //斜体
    italicAction = new QAction("斜体");
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered(bool)), this, SLOT(italic()));

    //图片
    imageAction = new QAction("图片");
    imageAction->setShortcut(tr("Ctrl+Shift+I"));
    connect(imageAction, SIGNAL(triggered(bool)), this, SLOT(image()));

    //链接
    linkAction = new QAction("链接");
    linkAction->setShortcut(tr("Ctrl+K"));
    connect(linkAction, SIGNAL(triggered(bool)), this, SLOT(link()));

    //语句间代码
    codeAction = new QAction("代码");
    codeAction->setShortcut(tr("Ctrl+Shift+`"));
    connect(codeAction, SIGNAL(triggered(bool)), this, SLOT(code()));

    //删除线
    mistakenAction = new QAction("删除线");
    mistakenAction->setShortcut(tr("Alt+Shift+5"));
    connect(mistakenAction, SIGNAL(triggered(bool)), this, SLOT(mistaken()));

    //水平线
    horizonAction = new QAction("水平线");
    horizonAction->setShortcut(tr("Ctrl+L"));
    connect(horizonAction, SIGNAL(triggered(bool)), this, SLOT(horizon()));

    //引用
    blockquoteAction = new QAction("引用");
    blockquoteAction->setShortcut(tr("Ctrl+Shift+Q"));
    connect(blockquoteAction, SIGNAL(triggered(bool)), this, SLOT(blockquote()));

    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveFileAction);
    operationMenu->addAction(strongAction);
    operationMenu->addAction(italicAction);
    operationMenu->addAction(h1Action);
    operationMenu->addAction(h2Action);
    operationMenu->addAction(h3Action);
    operationMenu->addAction(h4Action);
    operationMenu->addAction(h5Action);
    operationMenu->addAction(h6Action);
    operationMenu->addAction(imageAction);
    operationMenu->addAction(linkAction);
    operationMenu->addAction(codeAction);
    operationMenu->addAction(mistakenAction);
    operationMenu->addAction(horizonAction);
    operationMenu->addAction(blockquoteAction);
}

/**
 * @brief MainWindow::newOneFile
 * 新建一个文件
 */
void MainWindow::newFile(){
    MainWindow* newWindow = new MainWindow;
    newWindow->show();
}

/**
 * @brief MainWindow::openOneFile
 * 打开一个文件
 */
void MainWindow::openFile(){
    fileName = QFileDialog::getOpenFileName(this);
    if(mainText->document()->isEmpty()){        //当前窗口为空，直接放入
       loadFile();
    }else{                                      //当一个窗口非空，新建窗口
       MainWindow* newWindow = new MainWindow;
       newWindow->loadFile();
       newWindow->show();
    }
}

void MainWindow::loadFile(){
    QFile file(fileName);
    QString str;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("open file"),tr("cannot open file %1:\n %2")
                             .arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream qTextStream(&file);
    while(!qTextStream.atEnd()){
        str = qTextStream.readLine();
        mainText->append(str);
    }
    file.close();
    setWindowTitle(fileName);
    return;
}

bool MainWindow::saveFile(){
    if(fileName == ""){                 //选择文件名和地址
        fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "");
    }
    if(fileName == "")  return false;
    fileName = fileName.toUtf8();
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("save file"),tr("cannot save file %1:\n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream qTextStream(&file);
    qTextStream << mainText->toPlainText();
    file.close();
    setWindowTitle(fileName);
    mainText->document()->setModified(false);
    //保存后进行处理
    if(firstTime){
        QMessageBox box(QMessageBox::Warning, "Style", "请选择输出样式：\n");
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No |  QMessageBox::Apply | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Yes, QString("内联CSS"));
        box.setButtonText(QMessageBox::No, QString("外部CSS"));
        box.setButtonText(QMessageBox::Apply, QString("无CSS"));
        box.setButtonText(QMessageBox::Cancel, QString("取消"));
        int button = box.exec();
        if(button == QMessageBox::Yes){
            Values::isInlineCSS = true;
        }else if(button == QMessageBox::No){
            Values::isOutCSS = true;
        }else if(button == QMessageBox::Cancel){
            return true;
        }
        isOutCSS = Values::isOutCSS;
        isInlineCSS = Values::isInlineCSS;
        firstTime = false;
    }
    Values::isOutCSS = isOutCSS;
    Values::isInlineCSS = isInlineCSS;
    string htmlName = fileName.toStdString().substr(0, fileName.toStdString().size() - 2) + "html";
    Parser parser(fileName.toStdString().c_str() , htmlName.c_str());
    parser.Handle();
    return true;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (mainText->document()->isModified()){
        int temp = QMessageBox::information(this, "Message", "文件未保存，是否保存？", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (temp == QMessageBox::Yes){              //保存
            if(saveFile()){
                event->accept();
            }else{
                event->ignore();
            }
        }
        else if(temp == QMessageBox::No){           //不保存
            event->accept();
        }else{                                      //取消关闭
            event->ignore();
        }
    }
    else{
        event->accept();
    }
}

///**
// * @brief MainWindow::mergeFormat
// * @param fmt
// * 设置光标的选区
// */
//void MainWindow::selectBlock(QTextCharFormat fmt){
//    QTextCursor cursor = mainText->textCursor();
//    if (!cursor.hasSelection()) {
//       cursor.select(QTextCursor::WordUnderCursor);
//    }
//    cursor.mergeCharFormat(fmt);
//}

void MainWindow::strong(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(qTextCursor.hasSelection()){                         //光标选中
        int start = qTextCursor.selectionStart();
        int end = qTextCursor.selectionEnd();
        qTextCursor.setPosition(start);
        qTextCursor.insertText("**");
        qTextCursor.setPosition(end + 2);
        qTextCursor.insertText("**");
    }else{                                                  //光标未选中
        qTextCursor.movePosition(QTextCursor::StartOfLine);
        qTextCursor.insertText("**");
        qTextCursor.movePosition(QTextCursor::EndOfLine);
        qTextCursor.insertText("**");
    }
}

void MainWindow::italic(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(qTextCursor.hasSelection()){
        int start = qTextCursor.selectionStart();
        int end = qTextCursor.selectionEnd();
        qTextCursor.setPosition(start);
        qTextCursor.insertText("*");
        qTextCursor.setPosition(end + 1);
        qTextCursor.insertText("*");
    }else{
        qTextCursor.movePosition(QTextCursor::StartOfLine);
        qTextCursor.insertText("*");
        qTextCursor.movePosition(QTextCursor::EndOfLine);
        qTextCursor.insertText("*");
    }
}

void MainWindow::h1(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("# ");
    }
}

void MainWindow::h2(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("## ");
    }
}

void MainWindow::h3(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("### ");
    }
}

void MainWindow::h4(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("#### ");
    }
}

void MainWindow::h5(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("##### ");
    }
}

void MainWindow::h6(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("###### ");
    }
}

void MainWindow::image(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(!qTextCursor.hasSelection()){
        qTextCursor.insertText("![]()");
        qTextCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 3);
        mainText->setTextCursor(qTextCursor);                   //移动光标位置
    }
}

void MainWindow::link(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(!qTextCursor.hasSelection()){
        qTextCursor.insertText("[]()");
        qTextCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 3);
        mainText->setTextCursor(qTextCursor);                   //移动光标位置
    }
}

void MainWindow::code(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(qTextCursor.hasSelection()){
        int start = qTextCursor.selectionStart();
        int end = qTextCursor.selectionEnd();
        qTextCursor.setPosition(start);
        qTextCursor.insertText("`");
        qTextCursor.setPosition(end + 1);
        qTextCursor.insertText("`");
    }
}

void MainWindow::mistaken(){
    QTextCursor qTextCursor = mainText->textCursor();
    if(qTextCursor.hasSelection()){                         //光标选中
        int start = qTextCursor.selectionStart();
        int end = qTextCursor.selectionEnd();
        qTextCursor.setPosition(start);
        qTextCursor.insertText("~~");
        qTextCursor.setPosition(end + 2);
        qTextCursor.insertText("~~");
    }else{                                                  //光标未选中
        qTextCursor.movePosition(QTextCursor::StartOfLine);
        qTextCursor.insertText("~~");
        qTextCursor.movePosition(QTextCursor::EndOfLine);
        qTextCursor.insertText("~~");
    }
}

void MainWindow::horizon(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.insertText("---\n");
}


void MainWindow::blockquote(){
    QTextCursor qTextCursor = mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.insertText("> ");
}
