#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    count = 0;

    fileName = "";
    thisFileName = "";
    tempThisFileName = "";
    pdfThisFileName = "";
    htmlFileName = "";
    tempHtmlFileName = "";
    firstTime = true;
    isOutCSS = false;
    isInlineCSS = false;
    htmlWindow = nullptr;


//    QPalette pl = ui->mainText->palette();
//    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
//    ui->mainText->setPalette(pl);

//    ui->mainText ->setStyleSheet("background-color:rgb(255, 250, 250)");
    ui->mainText ->setStyleSheet("background-image:url(:/Picture/纸张.jpg)");



    htmlSyncTimer = new QTimer(this);
    connect(htmlSyncTimer,SIGNAL(timeout()),this,SLOT(onHtmlSyncTimerOut()));
    needToSync = false;
    modifiedTimer = new QTimer(this);
    connect(modifiedTimer,SIGNAL(timeout()),this,SLOT(onModifiedTimerOut()));
    isModified = false;
    modifiedTimer->start(100);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadFile(QString fileName){
    QFile file(fileName);
    QString str;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("open file"),tr("cannot open file %1:\n %2")
                             .arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream qTextStream(&file);
    ui->mainText->document()->clear();
    while(!qTextStream.atEnd()){
        str = qTextStream.readLine();
        ui->mainText->append(str);
    }
    file.close();
    ui->mainText->document()->setModified(true);
    setWindowTitle(fileName);
    thisFileName = fileName;                //设定本窗口打开的文件名
    htmlFileName = thisFileName.mid(0, thisFileName.size() - 2) + "html";       //设定相应的HTML文件名
    tempThisFileName = (thisFileName.mid(0, thisFileName.size() - 3) + "_temp.md").toUtf8();
    tempHtmlFileName = (thisFileName.mid(0, thisFileName.size() - 3) + "_temp.html").toUtf8();
    return;
}

bool MainWindow::saveFile(){
    if(thisFileName == ""){                 //选择文件名和地址
        thisFileName = QFileDialog::getSaveFileName(this, tr("Save as"), "", "MD (*.md)");
        if(thisFileName == ""){
            return false;
        }else {
            isModified = true;
        }
    }

    thisFileName = thisFileName.toUtf8();
    QFile file(thisFileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("save file"),tr("cannot save file %1:\n %2")
                             .arg(thisFileName).arg(file.errorString()));
        return false;
    }
    QTextStream qTextStream(&file);
    qTextStream << ui->mainText->toPlainText();
    file.close();
    setWindowTitle(thisFileName);

    handleFile();                           //处理文件

    if(isModified){
        parser(thisFileName, htmlFileName);
    }
    isModified = false;

    return true;
}

void MainWindow::handleFile(){
    //保存后进行处理
    if(firstTime){
        htmlFileName = (thisFileName.mid(0, thisFileName.size() - 2) + "html").toUtf8();       //设定相应的HTML文件名
        tempThisFileName = (thisFileName.mid(0, thisFileName.size() - 3) + "_temp.md").toUtf8();
        tempHtmlFileName = (thisFileName.mid(0, thisFileName.size() - 3) + "_temp.html").toUtf8();
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
            return;
        }
        isOutCSS = Values::isOutCSS;
        isInlineCSS = Values::isInlineCSS;
        firstTime = false;
        htmlWindow = new HTMLWindow();
        htmlWindow->show();
        htmlWindow->setWindowTitle(htmlFileName);
        needToSync = true;
        htmlSyncTimer->start(1000);
    }
    if(htmlWindow->isHidden()){                                     //窗口被关闭，重新打开
        htmlWindow = new HTMLWindow();
        htmlWindow->setWindowTitle(htmlFileName);
        htmlWindow->show();
        needToSync = true;
    }
    onHtmlSyncTimerOut();
}

void MainWindow::parser(QString inFileName, QString outFileName){
    Values::isOutCSS = isOutCSS;
    Values::isInlineCSS = isInlineCSS;
    Parser parser(inFileName.toStdString().c_str() , outFileName.toStdString().c_str());
    parser.Handle();
}

void MainWindow::closeEvent(QCloseEvent* event){
    if (isModified){
        int temp = QMessageBox::information(this, "Message", "文件未保存，是否保存？", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (temp == QMessageBox::Yes){              //保存
            if(saveFile()){
                event->accept();
                if(htmlWindow != nullptr){
                    htmlWindow->close();
                }
            }else{
                event->ignore();
            }
        }
        else if(temp == QMessageBox::No){           //不保存
            event->accept();
            if(htmlWindow != nullptr){
                htmlWindow->close();
            }
        }else{                                      //取消关闭
            event->ignore();
        }
    }
    else{
        event->accept();
        if(htmlWindow != nullptr){
            htmlWindow->close();
        }
    }

    //删除临时文件
    if(tempThisFileName != ""){
        remove(tempThisFileName.toStdString().c_str());
    }
    if(tempHtmlFileName != ""){
        remove(tempHtmlFileName.toStdString().c_str());
    }

}

void MainWindow::onHtmlSyncTimerOut(){
    if(tempThisFileName == "")  return;
    if(needToSync || ui->mainText->document()->isModified()){
//        qDebug() << count;
//        count++;
        QFile file(tempThisFileName);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,tr("save file"),tr("cannot save file %1:\n %2")
                                 .arg(thisFileName).arg(file.errorString()));
            return;
        }
        QTextStream qTextStream(&file);
        qTextStream << ui->mainText->toPlainText();
        file.close();

        parser(tempThisFileName, tempHtmlFileName);

        htmlWindow->loadFile(tempHtmlFileName);
        needToSync = false;
        ui->mainText->document()->setModified(false);
    }
}

void MainWindow::onModifiedTimerOut(){
    if(ui->mainText->document()->isModified()){
        isModified = true;
    }
}

void MainWindow::on_newFileAction_triggered(){
    MainWindow* newWindow = new MainWindow();
    newWindow->show();
}

void MainWindow::on_openFileAction_triggered(){
    fileName = QFileDialog::getOpenFileName(this);
    if(fileName == "")  return;
    if(ui->mainText->document()->isEmpty() && thisFileName == ""){          //当前窗口为空，且还未加载过文件，直接放入
        loadFile(fileName);
        handleFile();
    }else{                                                              //当一个窗口非空，新建窗口
        MainWindow* newWindow = new MainWindow();
        newWindow->loadFile(fileName);
        newWindow->handleFile();
        newWindow->show();
    }
}

void MainWindow::on_saveFileAction_triggered(){
    saveFile();
}

void MainWindow::on_saveFileButton_clicked(){
    on_saveFileAction_triggered();
}

void MainWindow::on_strongAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
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

void MainWindow::on_italicAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
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

void MainWindow::on_h1Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("# ");
    }
}

void MainWindow::on_h2Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("## ");
    }
}

void MainWindow::on_h3Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("### ");
    }
}

void MainWindow::on_h4Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("#### ");
    }
}

void MainWindow::on_h5Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("##### ");
    }
}

void MainWindow::on_h6Action_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    QString str = qTextCursor.selectedText();
    if(str.toStdString()[0] != '#'){
        qTextCursor.movePosition(QTextCursor::StartOfBlock);
        qTextCursor.insertText("###### ");
    }
}

void MainWindow::on_imageAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    if(!qTextCursor.hasSelection()){
        qTextCursor.insertText("![]()");
        qTextCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 3);
        ui->mainText->setTextCursor(qTextCursor);                   //移动光标位置
    }
}

void MainWindow::on_linkAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    if(!qTextCursor.hasSelection()){
        qTextCursor.insertText("[]()");
        qTextCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 3);
        ui->mainText->setTextCursor(qTextCursor);                   //移动光标位置
    }
}

void MainWindow::on_codeAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    if(qTextCursor.hasSelection()){
        int start = qTextCursor.selectionStart();
        int end = qTextCursor.selectionEnd();
        qTextCursor.setPosition(start);
        qTextCursor.insertText("`");
        qTextCursor.setPosition(end + 1);
        qTextCursor.insertText("`");
    }
}

void MainWindow::on_mistakenAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
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

void MainWindow::on_horizonAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.insertText("---\n");
}

void MainWindow::on_blockquoteAction_triggered(){
    QTextCursor qTextCursor = ui->mainText->textCursor();
    qTextCursor.movePosition(QTextCursor::StartOfBlock);
    qTextCursor.insertText("> ");
}

void MainWindow::on_strongButton_clicked(){
    on_strongAction_triggered();
}

void MainWindow::on_ItalicButton_clicked(){
    on_italicAction_triggered();
}

void MainWindow::on_imageButton_clicked(){
    on_imageAction_triggered();
}

void MainWindow::on_linkButton_clicked(){
    on_linkAction_triggered();
}

void MainWindow::on_codeButton_clicked(){
    on_codeAction_triggered();
}

void MainWindow::on_mistakenButton_clicked(){
    on_mistakenAction_triggered();
}

void MainWindow::on_horizonButton_clicked(){
    on_horizonAction_triggered();
}

void MainWindow::on_blockQuoteButton_clicked(){
    on_blockquoteAction_triggered();
}

void MainWindow::on_convertToPDFAction_triggered(){
//    qDebug() << htmlFileName;
//    qDebug() << pdfThisFileName;
//    qDebug() << thisFileName;
    if(htmlFileName == "" || thisFileName == "")  return;
    if(isModified){
        QMessageBox box(QMessageBox::Warning, "Style", "尚未保存，是否保存：\n");
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Yes, QString("是"));
        box.setButtonText(QMessageBox::No, QString("否"));
        box.setButtonText(QMessageBox::Cancel, QString("取消"));
        int button = box.exec();
        if(button == QMessageBox::Cancel){
            return;
        }else if(button == QMessageBox::Yes){
            saveFile();
        }
    }
    if(pdfThisFileName == ""){                 //选择文件名和地址
        pdfThisFileName = QFileDialog::getSaveFileName(this, tr("Convert To PDF As"), (thisFileName.mid(0, thisFileName.size() - 2) + "pdf").toUtf8(), tr("PDF (*.pdf)"));
    }
    if(pdfThisFileName == "")  return;   //叉掉了
    QProcess* process = new QProcess(this);
    process->start("wkhtmltopdf", QStringList() << htmlFileName << pdfThisFileName);
    process->waitForFinished();
}
